import sqlite3, serial, time

with sqlite3.connect("sqlite.db") as conn:
    print(type(conn))

    cur = conn.cursor()

    try:
        cur.execute("""CREATE TABLE IF NOT EXISTS distance(distance);""")
       
        portUSB = "/dev/ttyUSB0"
        ser = serial.Serial(portUSB,baudrate=115200, dsrdtr=False)
        ligne = ser.readline()
        strlignes = ligne.decode("utf-8")
        strligne = strlignes.strip()

        cur.execute("""DELETE FROM distance""")
        cur.execute("""INSERT INTO distance (distance) VALUES (?)""",(strligne,))

        while True:

            time.sleep(1)
            ligne=ser.readline()
            strlignes = ligne.decode("utf-8")
            strligne = strlignes.strip()
            print(strligne)
            cur.execute("""UPDATE distance SET distance = ?""",(strligne,))
            conn.commit()

            try:

                cur.execute("""SELECT * FROM mode""")
                list = cur.fetchall()
                tuple = list[0]
                boolean = tuple[0]

                if boolean == 1:
                    data = "auto"

                else:
                    data = "manual"
                
                encoded_data = data.encode("utf-8")
                ser.write(encoded_data)
        
            except sqlite3.DatabaseError as e:
                print("Failed to read DB : \n", e)
    
    except sqlite3.DatabaseError as e:
        print("Something happened : \n", e)
