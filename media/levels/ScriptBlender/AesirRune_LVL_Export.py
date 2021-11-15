#                     Copyright © 
# Juan Carlos Soria Salto & Dolores Santiago Castillo 
#                        2021
bl_info = {
    "name": "AesirRune Level Export",
    "author": "Juan Carlos Soria Salto & Dolores Santiago Castillo ",
    "version": (1, 3),
    "blender": (2, 80, 0),
    "location": "File > Export",
    "description": "Export VikinGO Level (JSON)",
    "warning": "",
    "doc_url": "",
    "category": "Export File",
}

import bpy, os, json

def write_some_data(context, filepath):
    # Creamos un array y metemos todos los objetos que componen la escena
    objetos = bpy.data.objects
    
    # Seteamos la ruta de salida y el nombre de nuestro archivo JSON y abrimos
    # el documento creado para comenzar a escribir en él
    file = open(filepath, "w", encoding='utf-8')

    # Creamos una variable para inicializar la estructura de objetos de JSON
    # Creamos tambien una variable acumuladora que almacenara todos los datos que deseemos escribir
    result = "{\n"
    resultJson = ""
    
    string1 = "nombreObjetoBlender+_path"
    string2 = "carpeta/objeto.obj"
    
    result += '"' + string1 + '"' + ': ' + json.dumps(string2) + ',' + '\n'  
    result += '\n'
    result += '\n'
    result += '\n'
    result += '\n'

    # ____________________________________________________________________________________________________________________________________
    #
    # -------------------------------------------------------- SCRIPT GENERAL ------------------------------------------------------------
    # ____________________________________________________________________________________________________________________________________
    #
    
    # Realizamos un bucle para sacar el tamaño del array
    size = 0
    
    for it in objetos:
        size += 1
    
    # Variables para los objetos 
    lista = []
    indiceObjetos = 0
    numeros = []
    
    # Variables para los colliders
    numerosCol = []
    colliders = []
    
    # Variables para los key y aux points
    numKeyPoints = []
    numAuxPoints = []
    keypoints = []
    auxpoints = []
    
    # Realizamos un bucle para realizar una lista con los nombres de los objetos que hay
    for iterator in objetos:
        todo = iterator.name.split()
        lista.append(todo[0])
        
    # Creamos una variable que nos dira cuando estamos en la ultima posicion del array
    aux = 0
    
    # Realizamos un while para recorrer todos los objetos de la escena y rellenar los arrays numeros (objetos) y colliders
    while aux < size - 1:
        miNombre = objetos[aux].name.split()
        miSiguienteNombre = objetos[aux + 1].name.split() 
        
        if((miNombre[0] != miSiguienteNombre [0] and miNombre[0] != "Collider" and miNombre[0] != "KeyPoint" and miNombre[0] != "AuxPoint") or aux == size - 2):
            nombre = miNombre[0]
            numeros.append(nombre)            
            veces = lista.count(nombre)
            numeros.append(veces)
        
        aux = aux + 1
        
        # Si el name del objeto es Collider, lo anyadimos a un array aparte para saber las colisiones de los objetos
        if miNombre[0] == "Collider":
            nombreCol = miNombre[0]
            colliders.append(nombreCol)
            lengthColliders = len(colliders)
        # Si el name del objeto es KeyPoint, lo anyadimos a un array aparte para saber las key del mapa
        if miNombre[0] == "KeyPoint":
            nombreKey = miNombre[0]
            keypoints.append(nombreKey)
            lengthKey = len(keypoints)
        # Si el name del objeto es AuxPoint, lo anyadimos a un array aparte para saber las aux del mapa
        if miNombre[0] == "AuxPoint":
            nombreAux = miNombre[0]
            auxpoints.append(nombreAux)
            lengthAux = len(auxpoints)
            
    # Prints de testeo
    print(colliders)
    print(lengthColliders)
    print(numeros)
    
    # ____________________________________________________________________________________________________________________________________
    #
    # ------------------------------------------------- CREACION DE INFORMACION DEL JSON -------------------------------------------------
    # ____________________________________________________________________________________________________________________________________
    #
    
    # CABECERA COLLIDERS: Mostras al principio la cantidad de colliders que hay en el mapa
    stringAuxCollider = "Colliders"
    result += '"' + stringAuxCollider + '"' + ': ' + json.dumps(len(colliders)) + ',' + '\n'
    
    result += '\n'
    end = 0
    
    
    # COLLIDERS: Recorremos el array de objetos de la escena y llenamos informacion de los COLLIDERS
    for selCol in objetos:
        colliderScene = selCol.name.split()
        
        if colliderScene[0] == "Collider":
            loc = selCol.location
            esc = selCol.scale
        
            resultJson = [loc.x, loc.y, loc.z, esc.x, esc.y, esc.z] 
            
            if(end == size):
                result += '"' + selCol.name + '"' + ': ' + json.dumps(resultJson) + '\n'
            else:
                result += '"' + selCol.name + '"' + ': ' + json.dumps(resultJson) + ',' + '\n'
                
    result += '\n'
    
    # CABECERA COLLIDERS: Mostras al principio la cantidad de colliders que hay en el mapa
    stringAuxCollider = "KeyPoints"
    result += '"' + stringAuxCollider + '"' + ': ' + json.dumps(len(keypoints)) + ',' + '\n'
    
    result += '\n'
    end = 0
    
    
    # COLLIDERS: Recorremos el array de objetos de la escena y llenamos informacion de los COLLIDERS
    for selCol in objetos:
        colliderScene = selCol.name.split()
        
        if colliderScene[0] == "KeyPoint":
            loc = selCol.location
            esc = selCol.scale
        
            resultJson = [loc.x, loc.y, loc.z, esc.x, esc.y, esc.z] 
            
            if(end == size):
                result += '"' + selCol.name + '"' + ': ' + json.dumps(resultJson) + '\n'
            else:
                result += '"' + selCol.name + '"' + ': ' + json.dumps(resultJson) + ',' + '\n'
                
    result += '\n'
    
       # CABECERA COLLIDERS: Mostras al principio la cantidad de colliders que hay en el mapa
    stringAuxCollider = "AuxPoints"
    result += '"' + stringAuxCollider + '"' + ': ' + json.dumps(len(auxpoints)) + ',' + '\n'
    
    result += '\n'
    end = 0
    
    
    # COLLIDERS: Recorremos el array de objetos de la escena y llenamos informacion de los COLLIDERS
    for selCol in objetos:
        colliderScene = selCol.name.split()
        
        if colliderScene[0] == "AuxPoint":
            loc = selCol.location
            esc = selCol.scale
        
            resultJson = [loc.x, loc.y, loc.z, esc.x, esc.y, esc.z] 
            
            if(end == size):
                result += '"' + selCol.name + '"' + ': ' + json.dumps(resultJson) + '\n'
            else:
                result += '"' + selCol.name + '"' + ': ' + json.dumps(resultJson) + ',' + '\n'
                
    result += '\n'
    
    
    # CABECERA OBJETOS
    stringaux = "cabeceraObjetos"
    result += json.dumps(stringaux) + ': ['
    
    i = 0
    
    # Para poner el nombre de cada objeto en la cabecera "Objetos" [...]
    while i < len(numeros):
        if(i == len(numeros) - 2):
            result += json.dumps(numeros[i]) + "]," + '\n'
        else:
            result += json.dumps(numeros[i]) + ", "
        i = i + 2
    
    result += '\n'
    
    aux2 = 0
    
    # Para guardar la cantidad de cada objeto junto a su nombre "Arbol" : 5,
    while aux2 <= len(numeros) - 2:
        nombre = numeros[aux2]
        numero = numeros[aux2 + 1]
        result += '"' + nombre + '"' + ': ' + json.dumps(numero) + ',' + '\n'
        
        aux2 = aux2 + 2
        
    result += '\n'
    
    # Recorremos el array de objetos de la escena y llenamos informacion de los objetos NO COLLIDERS
    for sel in objetos:
        colliderScene = sel.name.split()
        
        # Excluimos los que son colliders
        if colliderScene[0] != "Collider" and colliderScene[0] != "KeyPoint" and colliderScene[0] != "AuxPoint":
            end = end + 1
            
            # posicion en cada eje
            # rotacion en cada eje
            # escalado en cada eje
            loc = sel.location
            rot = sel.rotation_euler
            esc = sel.scale
        
            resultJson = [loc.x, loc.y, loc.z, rot.x, rot.y, rot.z, esc.x, esc.y, esc.z] # LOLA
            # TODO: guardar texturas para cuando tengamos
                            
            # Check de si estamos en la ultima posicion  (Pura maquetacion para la sintaxis JSON)          
            # Si estamos en la ultima posicion no añadimos una coma, en el caso contrario si
            if(end == (size - len(colliders) - len(keypoints) - len(auxpoints))):
                result += '"' + sel.name + '"' + ': ' + json.dumps(resultJson) + '\n'
            else:
                result += '"' + sel.name + '"' + ': ' + json.dumps(resultJson) + ',' + '\n'
                result += '\n'

    # Añadimos una llave final que cierra el objeto padre de nuestro fichero JSON
    result = result[:-1]
    result = result +'\n}'
    
    # Escribimos el valor leido de la escena y cerramos el fichero JSON creado
    file.write(result)
    file.close()
    return {'FINISHED'}

# ____________________________________________________________________________________________________________________________________
#
# ------------------------------------------------- TEMPLATES HELPERS DE BLENDER -----------------------------------------------------
# ____________________________________________________________________________________________________________________________________
#

# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator

class ExportSomeData(Operator, ExportHelper):
    """This appears in the tooltip of the operator and in the generated docs"""
    bl_idname = "export_test.some_data"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "Export VikinGO LVL"

    # ExportHelper mixin class uses this
    filename_ext = ".json"

    filter_glob: StringProperty(
        default="*.json",
        options={'HIDDEN'},
        maxlen=255,  # Max internal buffer length, longer would be clamped.
    ) 
    def execute(self, context):
        return write_some_data(context, self.filepath)


# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ExportSomeData.bl_idname, text="AesirRune Level Export")


def register():
    bpy.utils.register_class(ExportSomeData)
    bpy.types.TOPBAR_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportSomeData)
    bpy.types.TOPBAR_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()

    # test call
    bpy.ops.export_test.some_data('INVOKE_DEFAULT')