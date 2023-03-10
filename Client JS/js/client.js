const socket = new WebSocket('ws://localhost:81');
const statusSocket = document.getElementById('status');
const errorSocket = document.getElementById('error');
const sendSocket = document.getElementById('sendMessage');
const receiveSocket = document.getElementById('receiveMessages');

// Tentative Connexion
if (socket.readyState == 0)
{
  statusSocket.innerHTML = "Status : Le socket a été créé ! En attente de connexion ...";
}

// Connexion Ouverte
socket.addEventListener('open', () => {
  statusSocket.innerHTML = "Status : Connecté !";
});

// Connexion Fermée
socket.addEventListener('close', () => {
  statusSocket.innerHTML = "Status : Fermer (Le serveur à était fermer) !";
});

// Réception des Messages
socket.addEventListener('message', function (event) {
  const li = document.createElement('li');
  li.style.listStyleType = "none";
  li.textContent = "Message serveur : " + event.data; // event.data = message recu
  receiveSocket.appendChild(li); // Ajouter un élément à la liste
});

// Envoie des Messages
sendSocket.addEventListener('click', () => {
  const message = document.getElementById('saisiMessage').value;

  if (message.length != 0)
  {
    socket.send(message);
  }
});

// Eventuelles Erreurs
socket.addEventListener('error', function (event) {
  errorSocket.innerHTML = "Erreur WebSocket : " + event;
});