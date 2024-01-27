#input_strings = [ 
#"135.0000, 308.8810 , 133.0000, 32.8810 , 222.0000, -1.1190 , 222.0000, 308.8810",
#"133.0000, 32.8810 , 122.0000, -35.1190 , 113.0000, -266.1190 , 156.0000, -214.1190 , 187.0000, -155.1190 , 212.0000, -74.1190 , 222.0000, -1.1190",
#"-135.0000, 308.8810 , -222.0000, 308.8810 , -221.0000, -1.1190 , -135.0000, 31.8810",
#"-135.0000, 31.8810 , -221.0000, -1.1190 , -212.0000, -75.1190 , -191.0000, -142.1190 , -120.0000, -48.1190",
#"-120.0000, -48.1190 , -191.0000, -142.1190 , -163.0000, -203.1190 , -131.0000, -248.1190 , -82.0000, -291.1190 , -43.0000, -309.1190 , -95.0000, -101.11902",
#"113.0000, -266.1190 , 122.0000, -35.1190 , 113.0000, -66.1190 , 62.0000, -302.1190",
#"-43.0000, -309.1190 , 28.0000, -309.1190 , 62.0000, -302.1190 , -95.0000, -101.1190",
#"113.0000, -66.1190 , 82.0000, -119.1190 , 62.0000, -302.1190",
#"82.0000, -119.1190 , 45.0000, -151.1190 , 62.0000, -302.1190",
#"45.0000, -151.1190 , 16.0000, -162.1190 , 62.0000, -302.1190",
#"16.0000, -162.1190 , -37.0000, -155.1190 , 62.0000, -302.1190",
#"-37.0000, -155.1190 , -69.0000, -133.1190 , 62.0000, -302.1190"
#]

def normalize(x, y, width, height):
    return x / width * 2.0, y / height * 2.0

def triangulate(polygon):
    # This is a simple triangulation for convex polygons
    # For non-convex polygons, this method will not always work correctly
    tris = []
    for i in range(1, len(polygon) - 1):
        tris.append(polygon[0])
        tris.append(polygon[i])
        tris.append(polygon[i + 1])
    return tris

normalized_polygons = []
triangulated_vertices = []

# Screen dimensions
width = 500
height = 800

# Process input strings and apply the normalization and triangulation
for input_str in input_strings:
    # Parse the coordinates and normalize them
    coords = input_str.split(',')
    polygon = [normalize(float(coords[i].strip()), float(coords[i+1].strip()), width, height) for i in range(0, len(coords), 2)]
    normalized_polygons.append(polygon)

    # Triangulate the polygon
    tris = triangulate(polygon)
    triangulated_vertices.extend(tris)

count = 0

# Print the results
for vert in triangulated_vertices:
    print("{:.6f}f, {:.6f}f, {:.1f}f,".format(vert[0], vert[1], 0.0))
    count += 3

print("")
print(count)
