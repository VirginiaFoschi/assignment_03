/*document.addEventListener('DOMContentLoaded', function () {
    initializeChart();
    // Supponiamo che updateWaterLevel venga chiamata periodicamente con nuovi livelli
}); */

//let chart = null; // Variabile globale per mantenere il riferimento al grafico

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
/**
let waterLevels = []; // Array per memorizzare i livelli dell'acqua
let maxDataPoints = 20000; // Sostituisci N con il numero di minuti che vuoi visualizzare

function updateWaterLevel(newLevel) {
    const now = new Date(); // Data e ora corrente

    waterLevels.push({
        time: now,
        level: newLevel
    });

    // Mantieni solo gli ultimi N punti dati
    while (waterLevels.length > maxDataPoints) {
        waterLevels.shift();
    }

    // Aggiorna il grafico
    updateChart();
}


function initializeChart() {
    const ctx = document.getElementById('waterLevelChart').getContext('2d');
    chart = new Chart(ctx, {
        type: 'line', // Tipo di grafico: linea
        data: {
            datasets: [{
                label: 'Livello dell\'Acqua',
                backgroundColor: 'rgba(54, 162, 235, 0.5)',
                borderColor: 'rgba(54, 162, 235, 1)',
                data: [] // Dati iniziali vuoti
            }]
        },
        options: {
            scales: {
                x: [{
                    type: 'time',
                    time: {
                        unit: 'minute',
                        tooltipFormat: 'HH:mm'
                    },
                    scaleLabel: {
                        display: true,
                        labelString: 'Orario'
                    }
                }],
                y: [{
                    scaleLabel: {
                        display: true,
                        labelString: 'Livello dell\'acqua'
                    }
                }]
            },
            tooltips: {
                mode: 'index',
                intersect: false
            },
            hover: {
                mode: 'nearest',
                intersect: true
            }
        }
    });
}

function updateChart() {
    if (chart) {
        chart.data.labels = waterLevels.map(data => data.time);
        chart.data.datasets[0].data = waterLevels.map(data => data.level);
        chart.update();
    }
} */


/*Funzione per cambiare i valori delle label */
function changeLabel() {
    let sonar = document.getElementById("WaterLevel");
    let valve = document.getElementById("ValveLevel");
    let state = document.getElementById("Stato");
    //updateWaterLevel(dataRecived.Sonar);

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
    
    xhr.send(JSON.stringify({'value': inputValue}));
    // Gestisce la risposta dal server
    xhr.onload = function () {
        if(xhr.status === 201) {
            console.log("Post successfully created!") 
        }
    }
});

let slider = document.getElementById("inputValue");
    var output = document.getElementById("sliderValue");
    output.innerHTML = slider.value; // Mostra il valore iniziale del cursore

    // Aggiorna il testo dello span ogni volta che il valore del cursore cambia
    slider.oninput = function() {
        output.innerHTML = this.value;
    }
