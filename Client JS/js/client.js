// Récupère le chemin du fichier HTML
var path = window.location.pathname;
// Récupère le nom du fichier HTML
var page = path.split("/").pop();
// Création du websocket
const socket = new WebSocket('ws://localhost:81');
// Définition du status
const statusSocket = document.getElementById('status');
// Réponse JSON
var reponseJSON = null;

// Fonction pour crypter un mot de passe en SHA256
function sha256(password) 
{
  return CryptoJS.SHA256(password).toString();
}

// Fonction pour envoyer au serveur
function requestUser(type, path, page, contentMessage) 
{
  let msg;

  if (type == 1 || type == 2)
  {
    let username = document.getElementById("username").value;
    let password = document.getElementById("passwd").value;
    let hashedPassword = sha256(password);

    if (type == 1)
    { 
      msg = {
        type: "inscription",
        page: page,
        username: username,
        password: hashedPassword,
      };
    }
    else if (type == 2)
    {
      msg = {
        type: "connexion",
        path: path,
        page: page,
        username: username,
        password: hashedPassword,
      };
    }
  }
  else if (type == 3)
  {
    // On récupere avec le cookie
    let infoCookie = getFromCookie(2);

    msg = {
      type: "authentification",
      path: path, //
      username: infoCookie[0],
      password: infoCookie[1],
    };
  }
  else if (type == 4)
  {
    // On récupere l'username avec le cookie
    let usernameCookie = getFromCookie(1);
    // On va récuperer la date et l'heure
    let actualyDate = getDateHours();

    msg = {
      type: "message",
      path: path, //
      username: usernameCookie,
      content : contentMessage,
      date: actualyDate.date,
      heure: actualyDate.heure, 
    };
  }

  socket.send(JSON.stringify(msg));
}

// Fonction pour définir un cookie avec un nom, une valeur et une durée d'expiration
function setCookie(cvalue, cusername, cpassword, exminutes) 
{
  const d = new Date();
  d.setTime(d.getTime() + (exminutes*60*1000)); // Minutes

  let expires = "expires="+ d.toUTCString();

  let cookieObject = {
    loggedIn: cvalue,
    usernameCookie: cusername,
    passwordCookie: cpassword
  };

  let jsonString = JSON.stringify(cookieObject);
  document.cookie = `cookieObject=${jsonString}` + ";" + expires;

  console.log("document.cookie :", document.cookie);
}

// Fonction pour vérifier si l'utilisateur est connecter ou pas
function isLoggedIn() 
{
  // Récupération du cookie et vérification de la valeur de loggedIn
  const cookiesArray = document.cookie.split(';');

  for (let i = 0; i < cookiesArray.length; i++) 
  {
    const cookie = cookiesArray[i].trim();
    if (cookie.startsWith('cookieObject=')) 
    {
      const value = cookie.substring('cookieObject='.length, cookie.length);
      const parsedCookie = JSON.parse(value);

      return parsedCookie.loggedIn === "true";
    }
  }

  return false;
}

// Fonction qui récupere la date ainsi que l'heure
function getDateHours()
{
  const date = new Date();

  // Récupérer la date
  const jour = date.getDate();
  const mois = date.getMonth() + 1; // Les mois commencent à 0, donc ajouter 1
  const annee = date.getFullYear();
  const dateString = jour + '/' + mois + '/' + annee;

  // Récupérer l'heure
  const heures = date.getHours();
  const minutes = date.getMinutes();
  const secondes = date.getSeconds();
  const heureString = heures + ':' + minutes + ':' + secondes;

  // Retourner la date et l'heure sous forme d'un objet
  return {
    date: dateString,
    heure: heureString
  };
}

// Fonction qui récupere dans le cookie
function getFromCookie(type)
{
  const cookie = document.cookie;

  // Vérifie si la valeur de l'attribut "loggedIn" est "true"
  if (isLoggedIn()) {
    const cookieStartIndex = cookie.indexOf("cookieObject=");
    if (cookieStartIndex === -1) {
      return false; // Le cookie ne contient pas d'objet "cookieObject"
    }

    const cookieEndIndex = cookie.indexOf(";", cookieStartIndex);
    const cookieValue =
      cookieEndIndex === -1
        ? cookie.substring(cookieStartIndex + 13)
        : decodeURIComponent(cookie.substring(cookieStartIndex + 13, cookieEndIndex)); // Opérateur ternere

    const cookieObject = JSON.parse(cookieValue);

    // On va créer un tableau pour recup les elements

    if (type == 1)
    {
      return cookieObject.usernameCookie;
    }
    else if (type == 2)
    {
      let tabInfo = [];

      tabInfo[0] = cookieObject.usernameCookie;
      tabInfo[1] = cookieObject.passwordCookie;

      return tabInfo;
    }
  }

  return false;
}

// Connexion Fermée
socket.addEventListener('close', () => {
  statusSocket.innerHTML = "Status : Fermer (Le serveur à était fermer) !";
});

// Tentative Connexion
if (socket.readyState == 0)
{
  statusSocket.innerHTML = "Status : Le socket a été créé ! En attente de connexion ...";
}

// Selon ou on se situe
if (path == "/" || page ==  "index.php" || page == "inscription.php")
{
  // Connexion Ouverte
  socket.addEventListener('open', () => {
    statusSocket.innerHTML = "Status : Connecter !";
  });

  if (isLoggedIn()) // Si il est connecter
    {
      document.location.href = "client.php";
    }
    else // Si il est pas connecter
    {
      let btnInscription = btnConnexion = null;
      let noValidate = document.getElementById('noValidate');

      if (path == "/" || page ==  "index.php") // Page de connexion
      {
        btnConnexion = document.getElementById('btnConnexion');
        btnConnexion.addEventListener('click', () => 
        {
          requestUser(2, path, page, null);
        });
      }
      if (page == "inscription.php") // Page d'inscription
      {
        btnInscription = document.getElementById('btnInscription');
        btnInscription.addEventListener('click', () => 
        {
          requestUser(1, null, page, null);
        });
      }

    socket.onmessage = function (evt) // Lorsque le serveur répond
    { 
      reponseJSON = JSON.parse(evt.data); // On recupere en format json
      if (reponseJSON.Inscription) // Si c'est une inscription
      {
        if (reponseJSON.Inscription == "ilExiste") // Si il existe déjà
        {
          noValidate.style.color = "red";
          noValidate.innerHTML = "Ce nom d'utilisateur existe déjà !";
        }
        else if (reponseJSON.Inscription == "ilEstInscrit") // Si il est inscrit
        {
          setCookie("true", reponseJSON.Username, reponseJSON.Password, 10);
          document.location.href = "client.php";
        }
      }
      else if (reponseJSON.Connexion) // Si c'est une connexion
      {
        if (reponseJSON.Connexion == "ilExistePas") // Si il existe pas
        {
          noValidate.style.color = "red";
          noValidate.innerHTML = "Ce nom d'utilisateur existe pas !";
        }
        else if (reponseJSON.Connexion == "mdpPasBon") // Si mdp incorrect
        {
          noValidate.style.color = "red";
          noValidate.innerHTML = "Mot de passe incorrect !";
        }
        else if (reponseJSON.Connexion == "ilEstConnecter") // Si il est connecter
        {
          setCookie("true", reponseJSON.Username, reponseJSON.Password, 10);
          document.location.href = "client.php";
        }
      }
    }
  }
}
else if (path == "/client.php")
{
    if (isLoggedIn()) // Si il est connecter
    {
      var sendSocket;
      var receiveSocket;
      
      if (socket.readyState === WebSocket.OPEN) 
      {
        statusSocket.innerHTML = "Status : Connecter !";
        requestUser(3, path, null, null); // re authentification
      } 
      else 
      {
        // Attendre que la connexion soit ouverte
        socket.addEventListener('open', () => {
          statusSocket.innerHTML = "Status : Connecter !";
          requestUser(3, path, null, null); // re authentification
        });
      }

      // Réception des Messages
      socket.onmessage = function (evt)
      {
        reponseJSON = JSON.parse(evt.data); // On recupere en format json

        if (reponseJSON.Authentification) // Si c'est une authentication
        {
          if (reponseJSON.Authentification == "ilExistePas" || reponseJSON.Authentification == "mdpPasBon") // Si il existe pas ou mdp incorrect
          {
            document.location.href = "index.php"; // bah on le remet sur la page de connexion
          }
          else if (reponseJSON.Authentification == "ilEstConnecter") // Si il est connecter
          {
            sendSocket = document.getElementById('sendMessage');
            receiveSocket = document.getElementById('receiveMessages');

            // Envoie des Messages
            sendSocket.addEventListener('click', () => {
              const message = document.getElementById('saisiMessage').value; // On recup le message
              if (message.length != 0) // Si > 0 caractére
              {
                requestUser(4, path, null, message); // on le construit puis l'envoie
              }
            });
          }
        }
        else if (reponseJSON.Type == "message") // Si c'est un message
        {
          var li = document.createElement('li');
          li.style.listStyleType = "none";

          if (reponseJSON.Username == getFromCookie(1)) // Si c'est lui même
          {
            li.style.color = "blue";

            // Afficher comme envoie
            li.textContent = reponseJSON.Username + " : " + reponseJSON.Content + ", date : " + reponseJSON.Date + ", heure : " + reponseJSON.Heure; // event.data = message recu
          }
          else
          {
            li.style.color = "red";

            // Afficher comme reçu
            li.textContent = reponseJSON.Username + " : " + reponseJSON.Content + ", date : " + reponseJSON.Date + ", heure : " + reponseJSON.Heure; // event.data = message recu
          }

          receiveSocket.appendChild(li); // Ajouter un élément à la liste
        }
      };
    }
    else // Si il est pas connecter
    {
      document.location.href = "index.php";
    }
}