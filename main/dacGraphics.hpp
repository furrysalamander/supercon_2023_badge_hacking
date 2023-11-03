#include <memory>
#include <vector>

namespace dac {
    void update_buffer(std::unique_ptr<std::vector<uint8_t>> buffer);
    void init_dac();
}
