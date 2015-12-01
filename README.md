Ambient Sensor
===

**Tecnologías**: Arduino + Sensores + Azure EventHub + Stream Analytics + PowerBI

Descripción
---
Es un ejemplo de IoT que captura información de ambiente (Iluminación, Temperatura y Humedad) y la envía a Azure para su visualización en paneles de control en tiempo real en PowerBI, también se puede ver en el celular con una aplicación nativa o en el navegador. Se puede operar con los sensores para generar cambios en los diagramas.

**Modalidad**: Se prepara de un día para el otro.

**Requisitos**

* Arduino Uno R3, TMP36, DHT22, Termistor, Resistencia Cables, USB y Fuente (opcional). Todos provisos por Labs
* Conectividad Internet (con DHCP), Cable RJ45 y 220v.

Preparación
---

**Arduino**
El armado del board está en LabsAmbient.fzz y el código se encuentra en LabsAmbient\LabsAmbient.ino
Tener en cuenta que es necesaria una conexión de red RJ45 y algo que entregue direcciones DHCP.

**Power BI**
Por ahora se muestra la información de la última hora, se puede jugar un poco con los filtros para ver información más cercana. Para acceder a la configuración de la demo hay que entrar a app.powerbi.com con el usuario: labs@lagash.com/Password11

**Azure**
Esta demo depende de 3 servicios (se puede acceder con lagashlabs@outlook.com/Pa$$word11): 
* LabsAmbient (WebApp), el código se encuentra en el repositorio de GIT,
* LabsAmbient (Stream Analytics Job), éste último tiene que estar Started para que la información llegue a PowerBi. Se puede reiniciar y demora unos 10 minutos.
* LabsAmbient (Storage) que es el repositorio transitorio del Service Bus.

**Demo**
Conectar el Arduino a la PC o a la fuente y en 5 segundos empieza a enviar datos a Azure/PowerBI. Acceder a PowerBI (app.powerbi.com) para ver la última información. Para alterar los sensores de forma que sea evidente, se puede generar sombra (o iluminando con el celular) sobre el lector de iuminación (alto marron) o se pued soplar sobre el sensor de humedad (blanco) haciendo esto durante unos 10 segundos se verá el cambio en el reporte de PowerBI.
Si se conecta a la PC por USB se puede depurar con el cliente de Arduino y ver los datos en envía.

**Adaptación**: No tiene nada visual, salvo la información que se ve en PowerBI.

_Que se puede hacer_:

* En el futuro se puede hacer un actuador (enciende un led o suena un ruido cuando los valores exceden umbrales), pero hace falta 
* Se puede incorporar un sensor de humedad y controlar la humedad en una planta
* Se puede incorporar un sensor de presencia y saber si hay algo cerca.
* Se pueden armar queries en EventHubs y lanzar alramas.