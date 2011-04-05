def dumpdata2dot(nodes, edges, file):
	def writeln(text=""):
		file.write(text + "\n")

	writeln("digraph DAWG {");

	for nodeid, end in nodes:
		if end:
			writeln("node%d [shape=doublecircle, label=\"\"]" % nodeid)
		else:
			writeln("node%d [shape=circle, label=\"\"]" % nodeid)

	
	for srcid, char, dstid in edges:
		writeln("node%d -> node%d [label=\"%c\"]" % (srcid, dstid, str(char, "ascii")))

	writeln("}");


def dump2dot(dawg, file):
	nodes, edges = dawg.dump()
	dumpdata2dot(nodes, edges, file)
