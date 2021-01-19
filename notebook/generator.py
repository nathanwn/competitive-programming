import os
from ruamel.yaml import YAML

from tex_builder import TexBuilder


def main():
    os.system('rm -rf lib')
    os.system('cp -r ../lib lib')

    yaml = YAML(typ='safe')

    f = open('content.yml')
    yml_file_content = f.read()
    f.close()
    content = yaml.load(yml_file_content)

    tex = TexBuilder()

    for topic in content.keys():
        tex.section(topic)
        topic_dir = content[topic][0]['dir']
        subtopics = content[topic][1]['subtopics']

        for subtopic in subtopics:
            tex.subsection((subtopic['name']))
            file_path = '{0}/{1}'.format(topic_dir, subtopic['file'])
            tex.code_file(file_path)

    with open('content.tex', 'w') as f:
        f.write(tex.dump())

    os.system('latexmk -pdf -shell-escape main.tex')


if __name__ == "__main__":
    main()
