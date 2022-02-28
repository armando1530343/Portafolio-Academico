def kml(archivo):
	from xml.dom import minidom

	doc = minidom.parse('../PoliceForce_KML/' + archivo +'.kml')
	kml = doc.getElementsByTagName('kml')[0]
	document = kml.getElementsByTagName('Document')[0]
	placemarks = document.getElementsByTagName('Placemark')[0]
	MultiGeometry = placemarks.getElementsByTagName('MultiGeometry')[0]
	Polygon = MultiGeometry.getElementsByTagName('Polygon')[0]
	outerBoundaryIs = Polygon.getElementsByTagName('outerBoundaryIs')[0]
	LinearRing = outerBoundaryIs.getElementsByTagName('LinearRing')[0]
	coordinates = LinearRing.getElementsByTagName('coordinates')[0].firstChild.data
	coordinates = coordinates.replace(' ', '/')
	coordinates = coordinates.split('/')
	total_coord = len(coordinates)

	for i in range(total_coord):
		coordinates[i] = coordinates[i].split(',')
		coordinates[i][0] = float(coordinates[i][0])
		coordinates[i][1] = float(coordinates[i][1])
		coordinates[i][2] = float(coordinates[i][2])
		#print(coord[0])

	coordinates = np.array(coordinates)

	return max(coordinates[:,0]), max(coordinates[:,1]), min(coordinates[:,0]), min(coordinates[:,1])