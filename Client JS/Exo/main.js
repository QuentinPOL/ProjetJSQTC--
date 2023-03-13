
/*
// Exo 1
var btnExo1 = document.getElementById('btnExo1');
btnExo1.addEventListener("click", functionsExo1)

function functionsExo1(event)
{
    let longueur = prompt("Rentrez une longueur");
    let largeur = prompt("Rentrez une largeur");

    let perimetre = (longueur + largeur) * 2;
    let aire = longueur * largeur;

    alert("Le périmètre = " + perimetre + " et l'air = " + aire + " de votre rectangle");
}
*/

/*
// Exo 2
var btnExo2 = document.getElementById('btnExo2');
btnExo2.addEventListener("click", functionsExo2)

function functionsExo2(event)
{
    let diametre = prompt("Rentrez une longueur");

    let rayon = diametre / 2;

    let perimetre = diametre * Math.PI;
    let aire = Math.PI * Math.pow(rayon, 2);

    alert("Le périmètre = " + perimetre + " et l'air = " + aire + " de votre cercle");
}
*/

/*
// Exo 3
var a = 3, b = 2;

function multiple(x = 8) 
{
    return x * 3;
}

var btnExo3 = document.getElementById('btnExo3');
btnExo3.addEventListener("click", affiche)

function affiche(event) 
{
    alert(multiple(a));
    alert(multiple(b));
    alert(multiple());
}
*/

/*
// Exo 4
var tab = [-2, 1, 4];

function additionne(x) 
{
    return x + 2 ;
}

var btnExo4 = document.getElementById('btnExo4');
btnExo4.addEventListener("click", affiche)

function affiche(event) 
{
    for (let i = 0; i < tab.length; i++)
    {
        alert(additionne(tab[i]));
    }
}
*/

/*
// Exo 5
var btnExo5 = document.getElementById('btnExo5');
btnExo5.addEventListener("click", boucle)

function boucle(event) 
{
    var tab = [];
    tab.length = 3;

    for (let i = 0; i < tab.length; i++) 
    {
        tab[i] = Math.pow(i, 2);
    }

    for (let i = 0; i < tab.length; i++)
    {
        alert(tab[i]);
    }    
}

var btn2Exo5 = document.getElementById('btn2Exo5');
btn2Exo5.addEventListener("click", boucle2)

function boucle2(event) 
{
    let lenghtTable = prompt("Rentrez la longueur souhaitée du tableau !");
    
    let tableau = [];
    tableau.length = lenghtTable;

    for (let i = 0; i < tableau.length; i++) 
    {
        tableau[i] = Math.pow(i, 2);
    }

    for (let i = 0; i < tableau.length; i++)
    {
        alert(tableau[i]);
    }      
}
*/

/*
// Exo 6
var tab = [-2, 1, 4];

function soustrait(x) 
{
    if (x >= 0)
    {
        return x - 2;
    }
    else
    {
        return "Nombre négatif !";
    }
}

var btnExo6 = document.getElementById('btnExo6');
btnExo6.addEventListener("click", affiche)

function affiche(event) 
{
    for (let i = 0; i < tab.length; i++)
    {
        alert(soustrait(tab[i]));   
    }
}
*/

/*
// Exo 7
var btnExo7 = document.getElementById('btnExo7');
btnExo7.addEventListener("click", jourDeLaSemaine)

function jourDeLaSemaine(event) 
{
    var laDate = new Date();

    switch (laDate.getDay()) {
        case 1: alert("Nous sommes : Lundi");
          break;
        case 2: alert("Nous sommes : Mardi");
          break;

        case 3: alert("Nous sommes : Mercredi");
          break;

        case 4: alert("Nous sommes : Jeudi");
          break;

        case 5: alert("Nous sommes : Vendredi");
          break;

        case 6: alert("Nous sommes : Samedi");
          break;

        case 7: alert("Nous sommes : Dimanche");
          break;
    }
}
*/

// Exo 8
var divExo8 = document.getElementById('divExo8');
var monParametre = 5;

divExo8.addEventListener("mouseover", function(event) {
    // Ajoutez vos paramètres supplémentaires à l'objet event
    event.target.monParametre = 5;
    // Appelez votre fonction de rappel ici
    changementCouleur(event.target.monParametre);
});

divExo8.addEventListener("click", function(event) {
    // Ajoutez vos paramètres supplémentaires à l'objet event
    event.target.monParametre = 2;
    // Appelez votre fonction de rappel ici
    changementCouleur(event.target.monParametre);
});

divExo8.addEventListener("dblclick", function(event) {
    // Ajoutez vos paramètres supplémentaires à l'objet event
    event.target.monParametre = 3;
    // Appelez votre fonction de rappel ici
    changementCouleur(event.target.monParametre);
});

function changementCouleur(event)
{
    if (event == 5)
    {
        event.target.style.color = "red";
    }
    else if (event == 2)
    {
        event.target.style.color = "lime";
    }
    else if (event == 3)
    {
        event.target.style.color = "navy";
    }
}