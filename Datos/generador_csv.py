import csv
import random
import string

# --- CAMBIO: Listas de nombres y apellidos expandidas para mayor variedad ---
nombres_masculinos = [
    "Alejandro", "Andres", "Angel", "Antonio", "Carlos", "Cristian", "Daniel", "David", "Diego", "Eduardo",
    "Emilio", "Esteban", "Fabian", "Felipe", "Fernando", "Francisco", "Gabriel", "Guillermo", "Gustavo", "Hector",
    "Ivan", "Javier", "Jesus", "Jorge", "Jose", "Juan", "Julio", "Leonardo", "Luis", "Manuel", "Marco", "Mario",
    "Martin", "Mateo", "Miguel", "Nicolas", "Oscar", "Pablo", "Pedro", "Rafael", "Ricardo", "Roberto", "Rodrigo",
    "Samuel", "Santiago", "Sebastian", "Sergio", "Tomas", "Victor"
]
nombres_femeninos = [
    "Adriana", "Alejandra", "Alicia", "Ana", "Andrea", "Camila", "Carla", "Carmen", "Carolina", "Catalina",
    "Cecilia", "Clara", "Claudia", "Cristina", "Daniela", "Diana", "Elena", "Elizabeth", "Emilia", "Estefania",
    "Fabiana", "Fernanda", "Florencia", "Gabriela", "Isabel", "Javiera", "Jimena", "Josefa", "Juana", "Julia",
    "Laura", "Lucia", "Luisa", "Manuela", "Marcela", "Margarita", "Maria", "Mariana", "Marta", "Monica",
    "Natalia", "Paola", "Patricia", "Paulina", "Pilar", "Rosa", "Sandra", "Sofia", "Valentina", "Valeria", "Veronica"
]
apellidos = [
    "Garcia", "Rodriguez", "Gonzales", "Fernandez", "Lopez", "Martinez", "Sanchez", "Perez", "Gomez", "Martin",
    "Quispe", "Flores", "Rojas", "Mamani", "Diaz", "Torres", "Vargas", "Ruiz", "Castillo", "Jimenez", "Moreno",
    "Herrera", "Medina", "Castro", "Alvarez", "Romero", "Navarro", "Soto", "Acosta", "Rios", "Solis"
]

# Zonas del evento y su prioridad
zonas_persona = {
    "VIP": 5,
    "Platino": 4,
    "Prensa": 4,
    "General A": 2,
    "General B": 1,
    "Staff": 3,
    "Discapacitado": 2
}

# Nombre del archivo de salida
nombre_archivo = "personas_50k.csv"
num_registros = 50000

# --- CAMBIO: Generar DNIs únicos ---
# Se crea un rango de posibles DNIs y se elige una muestra aleatoria sin repetición.
print("Generando DNIs únicos...")
posibles_dnis = range(10000000, 99999999)
dnis_unicos = random.sample(posibles_dnis, num_registros)

# Generar los datos
print(f"Creando el archivo '{nombre_archivo}'...")
with open(nombre_archivo, mode='w', newline='', encoding='utf-8') as file:
    writer = csv.writer(file)
    writer.writerow(["DNI", "Nombre Completo", "Zona", "Prioridad", "Hora de Registro"])

    todos_nombres = nombres_masculinos + nombres_femeninos

    for i in range(num_registros):
        # Asignar un DNI único de la lista pre-generada
        dni = dnis_unicos[i]

        # --- CAMBIO: Generar nombres más variados ---
        nombre1 = random.choice(todos_nombres)
        apellido1 = random.choice(apellidos)
        apellido2 = random.choice(apellidos)

        # Asegurarse de que los dos apellidos no sean iguales
        while apellido1 == apellido2:
            apellido2 = random.choice(apellidos)

        # Combinar para formar un nombre completo más realista
        nombre_completo = f"{nombre1} {apellido1} {apellido2}"

        zona, prioridad = random.choice(list(zonas_persona.items()))

        hora = random.randint(8, 22)
        minuto = random.randint(0, 59)
        hora_registro = f"{hora:02d}{minuto:02d}"

        writer.writerow([dni, nombre_completo, zona, prioridad, hora_registro])

print(f"¡Listo! Se ha creado el archivo '{nombre_archivo}' con {num_registros} personas, DNIs únicos y nombres variados.")