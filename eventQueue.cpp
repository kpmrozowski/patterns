#include <memory>
#include <vector>
#include <iostream>

struct EventBase {
    virtual void Execute() = 0;
};

struct PrintMessage : public EventBase{
    PrintMessage(const char* str)
        : msg(str){
    }

    virtual void Execute() override {
        std::cout << msg << std::endl;
    }

    const char* msg;
};

struct EventQueue
{
    EventQueue() = default;
    ~EventQueue() = default;

    template<class EventType, typename... Args>
    void AddEvent(Args&&... args) 
    { 
        _events.emplace_back(std::make_unique<EventType>(std::forward<Args>(args)...)); 
    }

    void ExecuteAll() const 
    {
        for (auto &event : _events)
        { event->Execute(); } 
    }

private:
    std::vector<std::unique_ptr<EventBase>> _events;
};

int main()
{
    EventQueue q;
    q.AddEvent<PrintMessage>("Hello");
    q.ExecuteAll();
}
