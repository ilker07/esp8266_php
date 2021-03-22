#include <string.h>
String Host_name = "ILKER";
String password = "ilkeraykut07";

void RESET();

String Time();      


void setup(void) {
  Serial.begin(115200);
  RESET();
  
}

void loop(void) {

    Time();//Time Button.
     delay(2000);
}


void RESET()
{
  //Disconnecting previous networks
 
  sendData("AT+RST\r\n", 5000,1);
  
  sendData("AT+CWQAP\r\n", 5000,1); // Disconnect WiFi if connected.

  //Selecting Mode for WiFi
  
  sendData("AT+CWMODE=3\r\n", 1000,1); // configure as  both access point and station mode.

  

  //Searching for the wifi Connecrions.
  
  char inv = '"';
  delay(3000);
  
  sendData("AT+CWQAP\r\n", 4000,1); // again quit the connection if any.
  
  
  String conn = "AT+CWJAP";
  conn += "=";
  conn += inv;
  conn += Host_name;  // Host name
  conn += inv;
  conn += ",";
  conn += inv;
  conn += password; // Password
  conn += inv;
  conn += "\r\n\r\n";
  sendData(conn, 7000,1); // Join the connection.( AT+CWJAP = "Host_name","password" )

  

}
String Time()
{

 char inv = '"';
  String add = "AT+CIPSTART";
  add += "=";
  add += inv;
  add += "TCP";
  add += inv;
  add += ",";
  add += inv;
  add += "http://192.168.1.4";  //192.168.1.4/connect.php?&veri=125,https://www.facebook.com/
  add += inv;
  add += ",";
  add += "80";
  add += "\r\n";
  sendData(add, 3000,2);  // Establishing a TCP Connection. ( AT+CIPSTART = "TCP","Host_server_name",80)

  
  

 //AT+CIPSTART=2,"TCP","192.168.4.1",2222
      String hostt = "http://192.168.1.4/connect.php?&veri=1111 HTTP/1.1\r\n";
      //hostt +="\r\n";
      hostt += "Host:192.168.1.4\r\n";
      hostt +="Connection: close\r\n\r\n";
      //hostt += "\r\n\r\n\r\n\r\n\r\n";
      
      String rest = "AT+CIPSEND=";
      rest +=hostt.length();
      rest += "\r\n";
      //sendData(rest, 2000); //Number of characters to send. ( "AT+CIPSEND=90" )
      Serial.println(rest);
      delay(3000);
    
     // String Time = sendData(hostt, 2000);  // GET request ( GET /apps/thinghttp/send_request?api_key=XXXXXXXXXXXXXXXX 
      String Time=""; 
     Serial.println(hostt);
     delay(1000);
     Serial.println("AT+CIPCLOSE=0\r\n");
     delay(2000);
     return (Time);
   

}



String sendData(String command, const int Goldout,int beklenen)
{
  String response = "";
  
  
  Serial.print(command); // send the read character to the Serial1
  if (beklenen==1)
  while(Serial.find("OK"));
  else
   while(Serial.find("TCP"));
  
    while (Serial.available())
    {
      char c = Serial.read(); // read the next character.
      response += c;
    }
 

  //Serial.print("Response:");
  //Serial.println(response);
  
  return response;
}

//Resetteki at fonksiyonları yazilacak .Sonrasinda asagidakiler.
//AT+CIPSTART=2,"TCP","192.168.1.4",80
//AT+CIPSEND=2,35
//GET /connect.php?&veri=1234
//HTTP/1.1





