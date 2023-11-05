set(srcs 
    "main.cpp"
    "render.cpp"
    "uiDraw.cpp"
    "point.cpp"
    "rasterize.cpp"
    "game.cpp"
    "flyingObject.cpp"
    "velocity.cpp"
    "bullet.cpp"
    "rocks.cpp"
    "ship.cpp"
)

set(dirs ".")

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS "${dirs}")
