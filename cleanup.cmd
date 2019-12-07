@echo off

rmdir /s /q Debug
rmdir /s /q Release
rmdir /s /q x64

attrib -r -s -h *.ncb
attrib -r -s -h *.suo
attrib -r -s -h *.db
del *.ncb
del *.suo
del *.db

attrib -r -s -h .vs
rmdir /s /q .vs