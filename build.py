#sytuacja na rynku build systemów nadal beznadziejna
#to nic czego nie może zastąpić skrypt pythona

import subprocess
from os import *
from os.path import *

CC = "i686-elf-g++"
ASM = "nasm"
def allFilesIn(dir):
    return [f for f in listdir(dir) if isfile(join(dir,f))]

def allSourcesIn(dir,ext):
    return [f for f in allFilesIn(dir) if f.endswith(ext) ]

def cpp_cmd(infile, outfile, flags):
    str =" ".join(flags)+" -o "+outfile+" "+infile
    print(CC+" "+str)
    system(CC+" "+str)

def ass_cmd(infile, outfile, flags):
    str = " ".join(flags)+" "+infile+" -o "+outfile
    print(ASM+" "+str)
    system(ASM+" "+str)

compile_cmds = {".cpp":cpp_cmd, ".c":cpp_cmd, ".asm":ass_cmd}

#special global dirs
out_dir = "build"
src_dir = "src"

#dirs defined specificly for the project
klib_dir = join(src_dir,"klib")
cppabi_dir = join(src_dir,"cxxabi")

#dirs to pass to compiler as include paths
incl_dirs = [src_dir, klib_dir, cppabi_dir]

cppflags = ["-ffreestanding", "-std=c++17", "-Wall", "-Wextra", "-O2", "-fno-exceptions", "-fno-rtti"]+["-I "+f for f in incl_dirs]
asmflags = ["-felf32"]

def compileAllSourcesIn(dir,ext,flags):
    for file in allSourcesIn(dir,ext):
        fname, ext = splitext(file)
        outfile = join(out_dir, fname+".o")
        infile = join(dir, file)
        if getmtime(outfile) < getmtime(infile):
            compile_cmds[ext](infile,outfile,flags)
        else:
            print(infile+" unchanged, ommiting...")





def compile():
    crtbegin_file = subprocess.run([CC]+cppflags+["-print-file-name=crtbegin.o"], stdout = subprocess.PIPE).stdout
    crtend_file =   subprocess.run([CC]+cppflags+["-print-file-name=crtend.o"], stdout = subprocess.PIPE).stdout

    compileAllSourcesIn(klib_dir,".cpp",cppflags+[" -c"])

    compileAllSourcesIn(cppabi_dir,".cpp",cppflags+[" -c"])
    compileAllSourcesIn(cppabi_dir,".c",cppflags+[" -c"])
    compileAllSourcesIn(cppabi_dir,".asm",asmflags)

    compileAllSourcesIn(src_dir,".cpp",cppflags+[" -c"])
    compileAllSourcesIn(src_dir,".asm",asmflags)

    #special command

    begin_files = [join(out_dir,"crti.o"), crtbegin_file.decode('utf-8').strip()]
    end_files = [crtend_file.decode('utf-8').strip(), join(out_dir, "crtn.o")]

    exclude = ["crti.o", "crtn.o"]
    link_list = [join(out_dir, f) for f in allSourcesIn(out_dir, ".o") if f not in exclude]
    print(" ".join([CC]+["-o myos.bin","-T linker.ld","-nostdlib", "-lgcc"]+begin_files+link_list+end_files))
    system(" ".join([CC]+["-o myos.bin","-T linker.ld","-nostdlib", "-lgcc"]+begin_files+link_list+end_files))

if __name__ == '__main__':
    compile()
