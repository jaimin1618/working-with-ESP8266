data = ""

with open("index.html", "r", encoding="utf-8") as f:
    for line in f:
        line = line.replace("\"", "\'")
        data += "\"" + line.strip() + "\"" + "\n";
        
with open("output.txt", "w", encoding="utf-8") as f:
    f.write(data);