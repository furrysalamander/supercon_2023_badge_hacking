#include <memory>
#include <vector>

namespace dac {
    void update_buffer(std::unique_ptr<std::vector<std::array<uint8_t, 2>>> buffer);
    void init_continuous_dac();
    void output_coord(std::array<uint8_t, 2> point);
    void init_oneshot_dac();
    void render_thread();
}
