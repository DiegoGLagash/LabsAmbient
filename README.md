Ambient Sensor
Tecnologías: Arduino + Sensores + PowerBI
Descripción: Es un ejemplo de IoT que captura información de ambiente (Iluminación, Temperatura y Humedad) y la envía a Azure para su visualización en paneles de control en tiempo real en PowerBI, también se puede ver en el celular con una aplicación nativa o en el navegador. Se puede operar con los sensores para generar cambios en los diagramas.
Modalidad: Es una demo que se entrega el Arduino de Labs que debe prepararse para la demo, de un día para el otro.
Adaptación: No tiene nada visual, salvo la información que se ve en PowerBI.

Arduino
El armado del board está en LabsAmbient.fzz y el código se encuentra en LabsAmbient\LabsAmbient.ino
Tener en cuenta que es necesaria una conexión de red RJ45 y algo que entregue direcciones DHCP.

Power BI
Por ahora se muestra la información de la última hora, se puede jugar un poco con los filtros para ver información más cercana. Para acceder a la configuración de la demo hay que entrar a app.powerbi.com con el usuario: labs@lagash.com/Password11

Demo
Conectar el Arduino a la PC o a la fuente y en 5 segundos empieza a enviar datos a Azure/PowerBI. Acceder a PowerBI para ver la última información. Para tocar los sensores de forma que sea evidente, se puede generar sombra (o iluminando con el celular) sobre el lector de iuminación (alto marron) o se pued soplar sobre el sensor de humedad (blanco) haciendo esto durante unos 10 segundos se verá el cambio en el reporte de PowerBI.
Si se conecta a la PC por USB se puede depurar con el cliente de Arduino y ver los datos en envía.

Que se puede hacer:
	- En el futuro se puede hacer un actuador (enciende un led o suena un ruido cuando los valores exceden umbrales)
	- Se puede incorporar un sensor de humedad y controlar la humedad en una planta
	- Se puede incorporar un sensor de presencia y saber si hay algo cerca.