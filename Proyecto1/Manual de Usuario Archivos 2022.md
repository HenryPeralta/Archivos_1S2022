# Manual de Usuario
Para empezar a usar la aplicación podrá ejecutarla desde el ejecutable o podrá ejecutarlo desde la aplicación de QT creator.
 Una vez ejecutado la aplicación le aparecerá una terminal la cual le pedirá que ingrese un comando.
 ![enter image description here](https://i.ibb.co/q039GpV/1.jpg)

 ## MKDISK
Para empezar deberá colocar el comando mkdisk el cual tendrá como parámetros size, fit, unit y path. Este comando creara un disco el cual sera de tipo binario y con los parámetros indica el tamaño y la dirección en el que se creara.
![enter image description here](https://i.ibb.co/K5w6wXk/2.jpg)

 ## RMDISK
 Este comando sirve para borrar un disco creado, al ejecutar este comando saldrá un mensaje de confirmación para dar permiso de eliminar el disco. los para metros de este disco solo es path que es la dirección en el que se creo anteriormente. 
 ![enter image description here](https://i.ibb.co/LQFy65s/3.jpg)
 ## FDISK
 El comando fdisk sirve para agregar particiones primarias, extendidas y lógicas. Por disco solo pueden haber 4 particiones y solo puede haber un extendida y para las lógicas es obligatorio que haya un extendida. Las particiones creadas no pueden exceder el tamaño del disco y si son lógicas tampoco pueden exceder el tamaño de la partición extendida. los parámetros para este comando son size, unit, path, type, fit, delete, name y add, con estos comandos podemos crear particiones, agregar o quitarle espacio a una partición y también podemos eliminar la partición.
 ![enter image description here](https://i.ibb.co/4FkJmDf/4.jpg)
![enter image description here](https://i.ibb.co/PhN9N7x/5.jpg)
 ## MOUNT
 Este comando montara una partición del disco en el sistema y para cada partición montada se le creara un id único. Los parámetros para este comando son path y name donde path es la dirección del disco y name es el nombre de la partición
![enter image description here](https://i.ibb.co/7GkKsk0/6.jpg) 

 ## UNMOUNT
 El comando unmount desmonta la particion creada anteriormente. Los parámetros del comando unmount son solamente el id, que es el id generado por el comando mount.
 ![enter image description here](https://i.ibb.co/BP6D2t6/7.jpg)
 
 ## MKFS
 Este comando realiza un formateo completo de la particion, se formateara como ext2 o ext3 y creara un archivo en la raiz llamado users.txt que tendra los usuarios y contraseñas del sistema de archivos. Los parametros de este comando son id, type, fs.
![enter image description here](https://i.ibb.co/R76hgGJ/8.jpg)

 ## LOGIN
 Este comando se utilizara para iniciar sesión en el sistema.
 Los parametros para este comando son usuario, password      	y id.
 ![enter image description here](https://i.ibb.co/TrJZS5b/9.jpg)

  ## LOGOUT
  Este comando cierra la sesión
  ![enter image description here](https://i.ibb.co/sFrNPgh/10.jpg)
  
   ## REP
   Con este comando se podrán ver los reportes creados   del mbr y el disk. los parámetros de este comando son name, path y id. donde name tendrá el nombre del reporte, path tiene la dirección donde este se creara y id es el id de la partición.
   ![enter image description here](https://i.ibb.co/7yCPX43/11.jpg)
   
