template <typename Fn>
struct DeferFinalizer {
    Fn fn;
    bool moved;

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
    template <typename Fn>
    DeferFinalizer<Fn> operator<<(Fn &&f) {
        return DeferFinalizer<Fn>(f);
    }
};

inline static Deferrer deferrer;

#define TOKENPASTE(x, y) x##y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
#define defer \
    auto TOKENPASTE2(__deferred_lambda_call, __COUNTER__) = deferrer << [&]

