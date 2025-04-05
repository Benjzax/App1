import csv
import random
import sys
import datetime

# Si quieres más variedad, ajusta estas listas o agrégales más valores
PIZZA_NAMES = [
    "The Hawaiian Pizza", "The Classic Deluxe Pizza", "The Five Cheese Pizza", 
    "Margherita Pizza", "Pepperoni Pizza", "Chicken Supreme Pizza", "BBQ Chicken Pizza"
]
PIZZA_IDS = [
    "hawaiian", "classic_dlx", "five_cheese", 
    "margherita", "pepperoni", "chicken_supreme", "bbq_chicken"
]
PIZZA_SIZES = ["S", "M", "L", "XL"]
PIZZA_CATEGORIES = ["Classic", "Veggie", "Gourmet", "Spicy", "Special"]
PIZZA_INGREDIENTS = [
    "Sliced Ham, Pineapple, Mozzarella Cheese", 
    "Pepperoni, Mushrooms, Red Onions, Red Peppers, Bacon",
    "Mozzarella Cheese, Provolone Cheese, Gouda Cheese, Romano Cheese, Blue Cheese, Garlic",
    "Tomato, Mozzarella, Basil",
    "Pepperoni, Mozzarella, Tomato Sauce",
    "Chicken, Mozzarella, Onions, BBQ Sauce",
    "Bacon, Onion, Ham, Pineapple, Cheese"
]

def generar_fecha_aleatoria():
    """
    Genera una fecha aleatoria (formato M/D/YYYY) dentro del año 2015.
    """
    # Generamos una fecha aleatoria entre 2015-01-01 y 2015-12-31
    start_date = datetime.date(2015, 1, 1)
    end_date = datetime.date(2015, 12, 31)

    delta = end_date - start_date
    random_days = random.randint(0, delta.days)
    fecha = start_date + datetime.timedelta(days=random_days)
    # Formato deseado: M/D/YYYY
    return f"{fecha.month}/{fecha.day}/{fecha.year}"

def generar_hora_aleatoria():
    """
    Genera una hora aleatoria en formato HH:MM:SS (24h).
    """
    h = random.randint(0, 23)
    m = random.randint(0, 59)
    s = random.randint(0, 59)
    return f"{h:02d}:{m:02d}:{s:02d}"

def main():
    if len(sys.argv) < 2:
        print("Uso: python generar_filas_aleatorias.py <archivo_csv>")
        sys.exit(1)

    archivo_csv = sys.argv[1]

    # 1. Leer el CSV existente para:
    #    - Verificar si tiene encabezados
    #    - Encontrar el máximo 'pizza_id' y 'order_id' si deseas mantener correlativos
    #      (o simplemente generar IDs aleatorios; se muestra aquí un ejemplo).
    
    # Vamos a buscar si ya tiene encabezados y la fila de datos (para no reescribir encabezados)
    tiene_encabezados = False
    max_pizza_id = 0.0
    max_order_id = 0.0

    # Intentar leer el archivo existente
    try:
        with open(archivo_csv, "r", newline='', encoding="utf-8") as fr:
            reader = csv.reader(fr)
            # Leemos la primera línea y vemos si es encabezado
            header = next(reader, None)
            if header and "pizza_id" in header:  # Suponemos que es el encabezado oficial
                tiene_encabezados = True

            # Recorremos para hallar los mayores IDs
            # (Si no te interesa, puedes omitirlo o usar random)
            if tiene_encabezados:
                for row in reader:
                    try:
                        pid = float(row[0])  # pizza_id
                        oid = float(row[1])  # order_id
                        if pid > max_pizza_id:
                            max_pizza_id = pid
                        if oid > max_order_id:
                            max_order_id = oid
                    except:
                        pass
    except FileNotFoundError:
        print(f"El archivo '{archivo_csv}' no existe. Se creará uno nuevo.")
        # Si no existe, no hay encabezado ni ID previo, partimos de 0
    
    # 2. Generar 500 filas aleatorias
    nuevas_filas = []
    # Si no hay encabezados, definimos unos por defecto
    if not tiene_encabezados:
        nuevas_filas.append([
            "pizza_id","order_id","pizza_name_id","quantity","order_date",
            "order_time","unit_price","total_price","pizza_size","pizza_category",
            "pizza_ingredients","pizza_name"
        ])
    
    for i in range(500):
        # Incrementar ID o hacerlo aleatorio
        max_pizza_id += 1
        max_order_id += random.randint(0, 2)  # A veces repite order_id, a veces no, etc.

        # Elegir datos al azar
        idx_pizza = random.randint(0, len(PIZZA_NAMES) - 1)
        # Combinar con un sufijo de tamaño, por ejemplo "hawaiian_m"
        chosen_size = random.choice(PIZZA_SIZES)
        pizza_name_id = f"{PIZZA_IDS[idx_pizza]}_{chosen_size.lower()}"
        quantity = random.randint(1, 5)
        unit_price = round(random.uniform(5.0, 25.0), 2)
        total_price = round(unit_price * quantity, 2)
        fecha_aleatoria = generar_fecha_aleatoria()
        hora_aleatoria = generar_hora_aleatoria()
        categoria = random.choice(PIZZA_CATEGORIES)
        ingredientes = random.choice(PIZZA_INGREDIENTS)
        nombre_pizza = PIZZA_NAMES[idx_pizza]

        # Construir la fila
        fila = [
            f"{max_pizza_id:.2f}",
            f"{max_order_id:.2f}",
            pizza_name_id,
            f"{quantity:.2f}",
            fecha_aleatoria,
            hora_aleatoria,
            f"{unit_price:.2f}",
            f"{total_price:.2f}",
            chosen_size,
            categoria,
            f"\"{ingredientes}\"",  # Con comillas internas
            nombre_pizza
        ]
        nuevas_filas.append(fila)

    # 3. Escribir las 500 filas en el archivo CSV
    #    (modo 'a' para append si existe; 'w' si quieres sobrescribir, etc.)
    with open(archivo_csv, "a", newline='', encoding="utf-8") as fw:
        writer = csv.writer(fw)
        for fila in nuevas_filas:
            writer.writerow(fila)

    print(f"Se han agregado 500 filas aleatorias al archivo '{archivo_csv}'.")

if __name__ == "__main__":
    main()
