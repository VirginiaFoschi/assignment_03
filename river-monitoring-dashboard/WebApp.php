<?php

// URL di destinazione
$url = "http://example.com/api";

// Dati da inviare al server
$data = array('key1' => 'value1', 'key2' => 'value2');

// Inizializzazione di cURL
$ch = curl_init($url);

// Impostazione delle opzioni di richiesta
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_POST, true);
curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($data));

// Esecuzione della richiesta e ottenimento della risposta
$response = curl_exec($ch);

// Chiusura della sessione cURL
curl_close($ch);

// Gestione della risposta
if ($response === false) {
    echo "Errore nell'esecuzione della richiesta";
} else {
    echo "Risposta ricevuta: " . $response;
}
require ("template/WebApp.php");
?>