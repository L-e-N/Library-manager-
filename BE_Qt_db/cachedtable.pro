HEADERS       = connection.h \
                tableeditor.h
SOURCES       = main.cpp \
                tableeditor.cpp
QT           += sql widgets
#requires(qtConfig(tableview))

# install
target.path = /u/etu/promo2020/negre_leo/BE_Qt_db/cachedtable #TO ADAPT
INSTALLS += target
