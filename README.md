# Competitive-Programming-Notebook
This is a repository for Fast and Fourier - EAFIT ICPC Team Notebook.

The folder `code` contains most of the algorithms used by our team in the coding competitions: graph, strings, geometry, data structures, network flows, math, dynamic programming and other competitive programming stuff.

\
**NOTE:** Look `code/template.cpp` to unterstand macros in the codes.


# Generator Notebook Usage
Requires: [python](https://www.python.org/), [latexmk](https://www.ctan.org/pkg/latexmk/)

The python script `generate_pdf.py`generates the notebook in PDF, this script reads the contents of the notebook from `contents.txt`.


`contents.txt` has the following format:
```
[Section name]
subfolder/file.cpp  Description of the file      # Optional end-of-line comment
```
The python script was taken from [Stanford ICPC Notebook](https://github.com/jaehyunp/stanfordacm).
