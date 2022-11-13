#include <gtest/gtest.h>
#include <includes/function.h>
#include <includes/broadcaster.h>
#include <includes/holder.h>

Subscriptions::Holder holder;

class SubscriptionTests : public ::testing::Test {
protected:
    void SetUp() override {
        _triggerInt = false;
        _triggerFloat = false;
    }

protected:
    bool _triggerInt = false;
    bool _triggerFloat = false;

    const std::function<void(int)> intFunction = [&](int a) { _triggerInt = true; };
    const std::function<void(float)> floatFunction = [&](float b) { _triggerFloat = true; };
};

TEST_F(SubscriptionTests, testAddSubscriptions) {
    std::string eventId = "event";
    holder.subscribe(eventId, std::make_shared<Subscriptions::BaseFunction<void(int)>>(intFunction));
    holder.subscribe(eventId, std::make_shared<Subscriptions::BaseFunction<void(float)>>(floatFunction));

    Subscriptions::Broadcaster::getInstance()->send(eventId, int(1));
    Subscriptions::Broadcaster::getInstance()->send(eventId, float(2.2));

    ASSERT_EQ(_triggerInt, true);
    ASSERT_EQ(_triggerFloat, true);
}

TEST_F(SubscriptionTests, testRemoveSubscriptions) {
    holder.reset();

    std::string eventId = "event";
    Subscriptions::Broadcaster::getInstance()->send(eventId, int(1));
    Subscriptions::Broadcaster::getInstance()->send(eventId, float(2.2));

    ASSERT_EQ(_triggerInt, false);
    ASSERT_EQ(_triggerFloat, false);
}
