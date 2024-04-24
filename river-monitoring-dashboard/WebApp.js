let t = setInterval(getData, 2000);

let dataRecived = { 'Sonar': " ", 'Valve': " ", 'State': " " }

/*Funzione che richiede al server di ricevere i dati */
function getData() {
    let xhr = new XMLHttpRequest();
    let url = "http://localhost:8080";
    xhr.open('GET', url);
    // questa funzione verrà chiamata al cambio di stato della chiamata AJAX
    xhr.onreadystatechange = function () {
        let DONE = 4; // stato 4 indica che la richiesta è stata effettuata.
        let OK = 200; // se la HTTP response ha stato 200 vuol dire che ha avuto successo.
        if (xhr.readyState === DONE) {
            if (xhr.status === OK) {
                dataRecived = JSON.parse(xhr.responseText)
                console.log(dataRecived);
                changeLabel();
            } else {
                console.log('Error: ' + xhr.status); // Lo stato della HTTP response.
            }
        }
    };
    xhr.send();
}

/*Funzione per cambiare i valori delle label */
function changeLabel() {
    let sonar = document.getElementById("WaterLevel");
    let valve = document.getElementById("ValveLevel");
    let state = document.getElementById("Stato");


    sonar.innerText = "Sonar level: " + dataRecived.Sonar;
    valve.innerText = "Water level: " + dataRecived.Valve;
    state.innerText = "State: " + dataRecived.State;
}

/*Servono per rendere dinamica l'apparizione del form */
document.getElementById("Input").style.display = 'none';

document.getElementById("Change").addEventListener("click", function () {
    if (this.innerText == "Set Automatic Mode") {
        document.getElementById("Input").style.display = 'none';
        this.innerText = "Set Manual Mode";
    } else {
        document.getElementById("Input").style.display = 'block';
        this.innerText = "Set Automatic Mode";
    }

});

document.getElementById("Submit").addEventListener("click", function () {
    let inputValue = document.getElementById("inputValue").value;
    let xhr = new XMLHttpRequest();
    let url = "http://localhost:8080";
    xhr.open('POST', url);
    xhr.setRequestHeader("Content-Type", "application/json");

    xhr.send(JSON.stringify({ 'value': inputValue }));
    // Gestisce la risposta dal server
    xhr.onload = function () {
        if (xhr.status === 201) {
            console.log("Post successfully created!")
        }
    }
});

let slider = document.getElementById("inputValue");
var output = document.getElementById("sliderValue");
output.innerHTML = slider.value; // Mostra il valore iniziale del cursore

// Aggiorna il testo dello span ogni volta che il valore del cursore cambia
slider.oninput = function () {
    output.innerHTML = this.value;
}
