// Exo 10
var divX = document.getElementById("Methode1");
divX.addEventListener("click", FunctionChangeText);

function FunctionChangeText(evenement)
{
    if (evenement.target.className == "divName2") 
    {
        evenement.target.className = "newStyle";
    }
}

var div2 = document.getElementById("Methode2");
div2.addEventListener("mouseover", FunctionMouseOver);

function FunctionMouseOver(evenement) 
{
    evenement.target.style.visibility = "hidden";
}

function divClick() 
{
    alert("OOHOH ALERTE AU GOGOLES !");
}