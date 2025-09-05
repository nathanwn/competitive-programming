import os
from pathlib import Path


class TexBuilder:
    def __init__(self):
        self.tex = ''

    def append(self, s):
        self.tex = ''.join([self.tex, s])
        return self

    def curly(self, s):
        return self.append('{')\
                   .append(s)\
                   .append('}')

    def eol(self):
        return self.append('\n')

    def command(self, command_name, params=None, options=None):
        del options # for now
        if params is not None:
            params = ''.join(map(lambda p: '{0},'.format(p), params))[:-1]
        else:
            params = ''
        self.append('\\').append(command_name)
        if len(params) > 0:
            self.curly(params)
            self.eol()
        return self

    def section(self, section_name):
        return self.command('section', [section_name])

    def subsection(self, subsection_name):
        return self.command('subsection', [subsection_name])

    def code_file(self, filepath):
        filename, ext = os.path.splitext(Path(filepath).name)
        if ext in ['.cc', '.cpp', '.h', '.hpp']:
            filetype = 'cpp'
        elif ext in ['.java']:
            filetype = 'java'
        elif ext in ['.py']:
            filetype = 'python'
        elif ext == '' and filename == 'Makefile':
            filetype = 'basemake'
        else:
            assert False
        self.command('inputminted').curly(filetype).curly(filepath).eol()
        return self

    def dump(self):
        return self.tex


# def main():
#     tex = TexBuilder()
#     tex.section('section 1')\
#        .section('section 2')\
#        .section('section 3')\
#        .subsection('subsection 3.1')\
#        .subsection('subsection 3.2')\
#        .subsection('subsection 3.3')\
#        .code_file('lib/hello.cc')\
#        .code_file('lib/Makefile')
#     print(tex.dump())
#
#
# if __name__ == "__main__":
#     main()
