// Exo 9.1
function NameDiv(textName,  nameDiv) {
    alert("are u ready brooo ?");
    
    var element = document.getElementsByName(nameDiv);

    element.forEach(div => {
        div.innerHTML = textName;
    });
}

// Exo 9.X (commun)
var textReplaceName = prompt("Entrez du texte");
while (textReplaceName === "") 
{
    alert("T'a rien saisi !");
    textReplaceName = prompt("Entre du texte SALE NOOB BUUUU");
}

// Exo 9.1
NameDiv(textReplaceName, "test"); 