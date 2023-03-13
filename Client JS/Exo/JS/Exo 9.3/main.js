// Exo 9.3
function ClassNameDiv(textName,  nameDiv) {
    alert("are u ready brooo ?");
    
    var element = document.getElementsByClassName(nameDiv);

    for (var i = 0; i < element.length; i++)
    {
        element[i].innerHTML = textName;
    }
}

// Exo 9.X (commun)
var textReplaceName = prompt("Entrez du texte");
while (textReplaceName === "") 
{
    alert("T'a rien saisi !");
    textReplaceName = prompt("Entre du texte SALE NOOB BUUUU");
}

// Exo 9.3
ClassNameDiv(textReplaceName, "divName2"); 