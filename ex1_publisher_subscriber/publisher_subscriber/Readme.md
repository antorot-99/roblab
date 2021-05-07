# ESERCIZIO 1: PUBLISHER, SUBSCRIBER

L'esercizio chiedeva di implementare un canale di comunicazione tra un publisher e un subscriber per la posizione della posizione di 6 giunti

# Messaggio utilizzato

Il messaggio utilizzato per la comunicazione è JointTrajectoryPoint per definire le posizioni nel campo positions.
http://docs.ros.org/en/melodic/api/trajectory_msgs/html/msg/JointTrajectoryPoint.html

# Publisher

Il publisher crea il messaggio dando valori randomici alle 6 posizioni, successivamente li pubblica ad un canale nominato "chatter". Il messaggio viene successivamente stampato su terminale.

# Subscriber

Il subscriber riceve il messaggio dal canale "chatter". Il messaggio ricevuto viene stampato anche sul terminale.

Rotondo Antonio 0622701489
