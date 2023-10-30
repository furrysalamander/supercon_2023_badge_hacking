set(srcs 
    "main.cpp"
    "dacGraphics.cpp"
)

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS ".")
