set(srcs 
    "main.cpp"
    "render.cpp"
    "uiDraw.cpp"
    "point.cpp"
)

set(dirs ".")

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS "${dirs}")
