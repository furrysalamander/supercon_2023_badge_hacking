set(srcs 
    "main.cpp"
    "render.cpp"
)

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS ".")
