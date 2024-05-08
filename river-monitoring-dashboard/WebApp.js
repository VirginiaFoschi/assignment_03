const N = 30 //arco temporale di un minuto

document.addEventListener('DOMContentLoaded', function () {
    let t = setInterval(getData, 2000);
    let last = 0;
    let dps = [] 

    let chart = new CanvasJS.Chart("chartContainer", {
        title: {
            text: "Water Level Trend",
            fontColor: "#013A63"
        },
        axisX: {
            title: "Time in seconds",
            interval: 1,
            fontColor: "#013A63"
        },
        axisY: {
            title: "Water Level",
            interval: 1,
            fontColor: "#013A63"
        },
    backgroundColor: "#89C2D9",
        data: [{
            type: "line",
            color: "#012A4A" ,
            dataPoints: dps
        }]
    });

    chart.render();

    function getData() {
        last++;
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
                    updateGraph(dataRecived);
                } else {
                    console.log('Error: ' + xhr.status); // Lo stato della HTTP response.
                }
            }
        };
        xhr.send();
    }

    function updateGraph() {
        let xVal = dps.length == 0 ? 2 : dps[dps.length - 1].x + 2;
        let yVal = dataRecived.Sonar > 10 ? 0 : 10 - dataRecived.Sonar;
        dps.push({ x: xVal, y: yVal });
        console.log(dps)
        if (dps.length > N) {
            dps.shift();
        }

        chart.render()


    }

    function changeLabel() {
        let sonar = document.getElementById("WaterLevel");
        let valve = document.getElementById("ValveLevel");
        let state = document.getElementById("Stato");
        //updateWaterLevel(dataRecived.Sonar);

        sonar.innerText = "Water level: " + (dataRecived.Sonar > 10 ? 0 : 10 - dataRecived.Sonar);
        valve.innerText = "Valve Opening: " + dataRecived.Valve + "%";
        state.innerText = "State: " + dataRecived.State;
    }
    // update chart after specified time. 

    /*Servono per rendere dinamica l'apparizione del form */
    document.getElementById("Input").style.display = 'none';

    document.getElementById("Change").addEventListener("click", function () {
        if (this.innerText == "Set Automatic Mode") {
            document.getElementById("Input").style.display = 'none';
            this.innerText = "Set Manual Mode";
            sendMessage("Stop");
        } else {
            document.getElementById("Input").style.display = 'block';
            this.innerText = "Set Automatic Mode";
        }
    });

    function sendMessage(mesg) {
        let xhr = new XMLHttpRequest();
        let url = "http://localhost:8080";
        xhr.open('POST', url);
        xhr.setRequestHeader("Content-Type", "application/json");

        xhr.send(JSON.stringify({ 'value': mesg }));
        // Gestisce la risposta dal server
        xhr.onload = function () {
            if (xhr.status === 201) {
                console.log("Post successfully created!")
            }
        }
    }

    document.getElementById("Submit").addEventListener("click", function () {
        let inputValue = document.getElementById("inputValue").value;
        sendMessage(inputValue);
    });

    let slider = document.getElementById("inputValue");
    var output = document.getElementById("sliderValue");
    output.innerHTML = slider.value; // Mostra il valore iniziale del cursore

    // Aggiorna il testo dello span ogni volta che il valore del cursore cambia
    slider.oninput = function () {
        output.innerHTML = this.value;
    }
}
)

