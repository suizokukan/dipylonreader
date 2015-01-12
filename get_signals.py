# num. de connexion à récupérer
# faire le lien entre le signal et la connexion. 
import re

srcfilename = "cppdipylon/qt/sourceeditor.cpp"
#srcfilename = "cppdipylon/qt/scsplitter.cpp"

current_comments = []
current_function = ""
inside_slashstar = False

with open(srcfilename, 'r') as src:

	for _line in src:
		line = _line.strip()
		#print("?", line, inside_slashstar, line.startswith("//"))

		if len(line)==0:
			current_comments = []
			#print("FLUSH0", current_comments, line, inside_slashstar)
		elif line.startswith("//") and not inside_slashstar:
			line = line[2:]
			line = line.strip()
			if len(line)>0:
				current_comments.append(line+"X")
		elif line.startswith("/*"):
			line = line[2:]
			line = line.strip()
			inside_slashstar = True
			#print("!! inside_slashstar set to True")
			if len(line) > 0:
				current_comments.append(line+"Y")
		elif line.endswith("*/"):
			line = line[2:]
			line = line.strip()
			inside_slashstar = False
			#print("!! inside_slashstar set to False")
			if len(line) > 0:
				current_comments.append(line+"Z")
		elif inside_slashstar:
			if len(line) > 0:
				current_comments.append(line+"@")
		elif re.search("^([_a-zA-Z]+::[_a-zA-Z]+\()", _line) is not None:
			current_function = re.search("([_a-zA-Z]+::[_a-zA-Z]+)\("	, _line).group(0)
		else:
			#print("QObject::connect" in line, "emit" in line)
			if "emit" in line:
				print(current_function)
				print(line)
				print(current_comments)
				print("")
			elif "QObject::connect" in line:
				print(current_function)
				print(line)
				print(current_comments)
				print("")
			else:
				#print("FLUSH1", current_comments)
				pass