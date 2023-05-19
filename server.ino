#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

//const char* ssid = "FLIA PEREZ ";
//const char* password = "Familia01";

const char* ssid = "Conecta";
const char* password = "123456789";

AsyncWebServer server(80);

void handleRootPage(AsyncWebServerRequest *request) {
  // Servir la página de inicio de sesión
  request->send(SPIFFS, "/index.html", "text/html");
}

void handleDashboardPage(AsyncWebServerRequest *request) {
  // Verificar la autenticación del usuario antes de servir la página del dashboard

  // Si el usuario está autenticado, servir la página del dashboard
  request->send(SPIFFS, "/dashboard.html", "text/html");
}

void handleLogin(AsyncWebServerRequest *request) {
  // Obtener los datos de usuario y contraseña enviados desde el formulario
  String username = request->arg("username");
  String password = request->arg("password");

  // Realizar la validación del usuario y contraseña

  // Si la validación es exitosa, establecer una sesión o cookie para mantener al usuario autenticado

  // Redirigir al usuario al dashboard
  request->redirect("/dashboard");
}

void handleLogout(AsyncWebServerRequest *request) {
  // Realizar las acciones necesarias para cerrar la sesión del usuario (eliminar la sesión o cookie)

  // Redirigir al usuario a la página de inicio de sesión
  request->redirect("/");
}

void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin(true)) {
    Serial.println("No se pudo montar SPIFFS");
    return;
  }

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conexión WiFi establecida");
  Serial.println(WiFi.localIP());
  size_t totalBytes = SPIFFS.totalBytes();
  size_t usedBytes = SPIFFS.usedBytes();
  size_t freeBytes = totalBytes - usedBytes;
  
  Serial.printf("Tamaño total: %u bytes\n", totalBytes);
  Serial.printf("Bytes utilizados: %u bytes\n", usedBytes);
  Serial.printf("Bytes libres: %u bytes\n", freeBytes);

  // Configurar las rutas de las páginas web y los manejadores de eventos
  server.on("/", HTTP_GET, handleRootPage);
//  server.on("/dashboard", HTTP_GET, handleDashboardPage);
//  server.on("/login", HTTP_POST, handleLogin);
  server.on("/logout", HTTP_GET, handleLogout);

// Inicia el servidor
  server.begin();
}

void loop() {
}
