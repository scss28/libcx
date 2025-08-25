template <typename F>
class DeferFinalizer {
    F fn;
    bool moved;

   public:
    template <typename T>
    DeferFinalizer(T f) : fn(f), moved(false) {}

    DeferFinalizer(const DeferFinalizer &) = delete;

    DeferFinalizer(DeferFinalizer &&other)
        : fn(other.fn), moved(other.moved) {
        other.moved = true;
    }

    ~DeferFinalizer() {
        if (!moved) fn();
    }
};

struct Deferrer {
    template <typename F>
    DeferFinalizer<F> operator<<(F &&f) {
        return DeferFinalizer<F>(f);
    }
};

inline static Deferrer deferrer;

#define TOKENPASTE(x, y) x##y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
#define defer \
    auto TOKENPASTE2(__deferred_lambda_call, __COUNTER__) = deferrer << [&]

