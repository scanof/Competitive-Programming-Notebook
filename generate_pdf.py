import subprocess
import os
code_dir = "code"

def get_sections():
    sections = []
    section_name = None
    with open('contents.txt', 'r') as f:
        for line in f:
            if '#' in line: line = line[:line.find('#')]
            line = line.strip()
            if len(line) == 0: continue
            if line[0] == '[':
                if section_name is not None:
                    # Sort subsections alphabetically by display name (case-insensitive)
                    subsections.sort(key=lambda x: x[1].lower())
                    sections.append((section_name, subsections))
                section_name = line[1:-1]
                subsections = []
            else:
                tmp = line.split('\t', 1)
                if len(tmp) == 1:
                    raise ValueError('Subsection parse error: %s' % line)
                filename = tmp[0]
                subsection_name = tmp[1]
                if subsection_name is None:
                    raise ValueError('Subsection given without section')
                subsections.append((filename, subsection_name))
    # Sort the last section
    if section_name is not None and subsections:
        subsections.sort(key=lambda x: x[1].lower())
        sections.append((section_name, subsections))
    return sections

def get_style(filename):
    ext = filename.lower().split('.')[-1]
    if ext in ['c', 'cc', 'cpp', 'h']:
        return 'cpp'
    elif ext in ['java']:
        return 'java'
    elif ext in ['py']:
        return 'py'
    else:
        return 'txt'

# TODO: check if this is everything we need
def texify(s):
    #s = s.replace('\'', '\\\'')
    #s = s.replace('\"', '\\\"')
    return s

def filter_code(filename):
    """Read code file and filter out #include template.h and following empty line"""
    filepath = os.path.join(code_dir, filename)
    with open(filepath, 'r') as f:
        lines = f.readlines()

    # Filter out #include "../template.h" and the empty line after it
    filtered_lines = []
    skip_next = False
    for line in lines:
        if skip_next:
            # Skip the empty line after #include
            if line.strip() == '':
                skip_next = False
                continue
            else:
                # If it's not empty, don't skip it
                skip_next = False

        if '#include "../template.h"' in line or '#include"../template.h"' in line:
            skip_next = True
            continue

        filtered_lines.append(line)

    # Remove trailing blank lines
    while filtered_lines and filtered_lines[-1].strip() == '':
        filtered_lines.pop()
    # Ensure last line has no trailing newline (prevents lstinputlisting blank line)
    if filtered_lines and filtered_lines[-1].endswith('\n'):
        filtered_lines[-1] = filtered_lines[-1].rstrip('\n')

    # Write filtered content to temp file
    temp_filename = 'temp_' + filename.replace('/', '_')
    with open(temp_filename, 'w') as f:
        f.writelines(filtered_lines)

    return temp_filename

def get_tex_section(section_name, subsections):
    """Generate LaTeX for a single section"""
    tex = '\\section{%s}\n' % texify(section_name)
    for (filename, subsection_name) in subsections:
        tex += '\\subsection{%s}\n' % texify(subsection_name)
        temp_file = filter_code(filename)
        tex += '\\raggedbottom\\lstinputlisting[style=%s]{%s}\n' % (get_style(filename), temp_file)
        tex += '\\hrulefill\n'
    tex += '\n'
    return tex

def get_tex(sections):
    """Generate LaTeX for all sections - all will use 3 columns"""
    tex_all = ''

    for (section_name, subsections) in sections:
        # Skip the Fin section as it has no content
        if section_name == 'Fin':
            continue

        section_tex = get_tex_section(section_name, subsections)
        tex_all += section_tex

    return tex_all

if __name__ == "__main__":
    sections = get_sections()
    tex_all = get_tex(sections)

    # Write all content to a single file
    with open('contents.tex', 'w') as f:
        f.write(tex_all)

    latexmk_options = ["latexmk","-pdf", "notebook.tex"]
    subprocess.call(latexmk_options)
    remove_files = ["notebook.fls", "notebook.aux", "notebook.fdb_latexmk",
    "notebook.log", "notebook.out", "notebook.toc"]
    for file in remove_files:
        if os.path.exists(file):
            os.remove(file)
    # Clean up temp files
    for file in os.listdir('.'):
        if file.startswith('temp_') and file.endswith(('.cpp', '.py', '.java', '.txt', '.h', '.c', '.cc')):
            os.remove(file)
