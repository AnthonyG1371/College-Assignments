Contents in the "ftsoftds_Dev-C++" directory:

      All classes and libraries that are developed in the book are
      located as header files in the directory "include".
 
      The programs that are developed in the book are located in
      the corresponding chapter directory (ch1 and so forth).

      The directory "ezdraw" contains the graphics library for 
      Dev-C++ (ezd32m.lib)

         The directory also contains a dynamic link library
         "ezdraw32.dll" that must reside in the Windows/System
         directory and the file "ezdraw.ini" that belongs in the
         Windows directory. It may be necessary to set Windows Explorer
         so it will view hidden and system files in order to see
         "ezdraw32.dll".

            Copy:      "ezdraw32.ini"  to "c:\Windows\"
            Copy:      "ezdraw32.dll"  to "c:\Windows\System"

      The data files for the programs are in the "ftsoftds_Dev-C++"
      directory.
      
      The project file "program.dev" is set up to include the graphics
      library and the program "prg1_1.cpp".
      NOTE: You will need to add the "include" directory to
      the list of directories the compiler searches for include files.

