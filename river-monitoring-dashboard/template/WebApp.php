<!doctype html>
<html lang="it">

<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />

    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet"
        integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">

    <link rel="stylesheet" href="WebApp.css">


    <title>river-monitoring-dashboard</title>
</head>

<body class="bg-light">
    <h1>River monitoring dashboard</h1>
    <div>
        <label id="Stato">State:</label>
        <label id="H2O">Water Level:</label>
        <label id="valveOpening">Valve opening:</label>

        <button>Set Automatic Mode</button>
    </div>


    <form action="/submit" method="post">
        <label for="inputValue">Inserire valore apertura valvola:</label>
        <input type="text" id="inputValue" name="inputValue"><br><br>
        <button type="submit">Invia</button>
    </form>
</body>

</html>