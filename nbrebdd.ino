#include <SPI.h>
#include <Ethernet.h>

byte mac[6] = { 0xA8, 0x61, 0x0A, 0xAE, 0x66, 0x6A}; // Adresse MAC de l'ethernet card shield
byte ip [4] = {192,168,62,177}; // Adresse IP de l'Ethernet Shield et de la carte Arduino UNO
byte server [4] = {192,168,62,27}; // Adresse IP du PC où le serveur WAMP est installé
 
EthernetClient client; // deux choix possibles ici EthernetServer server(80) ou EthernetClient client;
 
void setup ()
{
Serial.begin (9600);// initialiser la liaison série à une vitesse de 9600bit/s
Ethernet.begin (mac, ip); // initialiser le shield Ethernet avec la variable mac et ip
delay (1000); // attendre 1000ms avant l'execution du programme principal

randomSeed(analogRead(0));
}

void loop ()
{
   long nombreA = random(10,30);
   Serial.println(nombreA);
  delay(1000);
 Serial.println ("Connexion en cours... ");//Afficher sur le moniteur série: Connexion en cours... 
 
if (client.connect(server, 80)) {   // Si la connection sur le serveur (via un éventuellement un port) est reussie
Serial.println("Connection sur le serveur reussie ! "); //Afficher sur le moniteur série: Connection sur le serveur reussie ! 
client.print("GET /index.php?valeurA=&valeurA");  http // Envoyer via la methode GET le nom de la variable qui contient le nombreA vers la page PHP
client.print(nombreA);   // Envoyer le nombre associé à la variable précédente

Serial.print(" Ecriture du nombre reussie: ");//Afficher sur le moniteur série: Ecriture du nombre reussie: ! 
client.println("HTTP/1.0"); // Envoyer le protocole utilisé, ici: HTTP/1.0
client.println("User-Agent: Arduino 1.0");
client.println();
Serial.println("Connecté!"); //Afficher sur le moniteur série: Connecté ! 
}
else
{
Serial.println(" Echec de connexion !");//Afficher sur le moniteur série: Echec de connexion !
}
if (client.connected()) {}
else {
Serial.println("Deconnection");
}
client.stop();
client.flush();
delay(10000); // Attendre 10s (10000 ms) jusqu'à la prochaine transmission de donnée
 
}
