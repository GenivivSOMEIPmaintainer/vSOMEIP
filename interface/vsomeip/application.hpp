// Copyright (C) 2014-2015 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef VSOMEIP_APPLICATION_HPP
#define VSOMEIP_APPLICATION_HPP

#include <memory>
#include <set>

#include <vsomeip/primitive_types.hpp>
#include <vsomeip/enumeration_types.hpp>
#include <vsomeip/constants.hpp>
#include <vsomeip/handler.hpp>

namespace vsomeip {

class configuration;
class event;
class payload;

class application {
public:
    virtual ~application() {}

    // get name
    virtual const std::string & get_name() const = 0;
    virtual client_t get_client() const = 0;

    virtual void set_configuration(const std::shared_ptr<configuration> _configuration) = 0;

    // Lifecycle
    virtual bool init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;

    // Provide services
    virtual void offer_service(service_t _service, instance_t _instance,
            major_version_t _major = DEFAULT_MAJOR, minor_version_t _minor =
                    DEFAULT_MINOR) = 0;

    virtual void stop_offer_service(service_t _service,
            instance_t _instance) = 0;

    virtual void offer_event(service_t _service,
            instance_t _instance, event_t _event,
            const std::set<eventgroup_t> &_eventgroups,
            bool _is_field) = 0;
    virtual void stop_offer_event(service_t _service,
            instance_t _instance, event_t _event) = 0;

    // Consume services
    virtual void request_service(service_t _service, instance_t _instance,
            major_version_t _major = ANY_MAJOR,
            minor_version_t _minor = ANY_MINOR,
            bool _use_exclusive_proxy = false) = 0;
    virtual void release_service(service_t _service, instance_t _instance) = 0;

    virtual void request_event(service_t _service, instance_t _instance,
            event_t _event, const std::set<eventgroup_t> &_eventgroups,
            bool _is_field) = 0;
    virtual void release_event(service_t _service, instance_t _instance,
            event_t _event) = 0;

    virtual void subscribe(service_t _service, instance_t _instance,
            eventgroup_t _eventgroup, major_version_t _major = DEFAULT_MAJOR,
            subscription_type_e _subscription_type = subscription_type_e::SU_RELIABLE_AND_UNRELIABLE) = 0;

    virtual void unsubscribe(service_t _service, instance_t _instance,
            eventgroup_t _eventgroup) = 0;

    virtual bool is_available(service_t _service, instance_t _instance) const = 0;

    // Send a message
    virtual void send(std::shared_ptr<message> _message, bool _flush = true) = 0;

    // Set a field or fire an event
    virtual void notify(service_t _service, instance_t _instance,
            event_t _event, std::shared_ptr<payload> _payload) const = 0;

    virtual void notify_one(service_t _service, instance_t _instance,
                event_t _event, std::shared_ptr<payload> _payload,
                client_t _client) const = 0;

    // [Un]Register handler for state change events
    virtual void register_state_handler(state_handler_t _handler) = 0;
    virtual void unregister_state_handler() = 0;

    // [Un]Register message handler for a method/an event/field
    virtual void register_message_handler(service_t _service,
            instance_t _instance, method_t _method,
            message_handler_t _handler) = 0;
    virtual void unregister_message_handler(service_t _service,
            instance_t _instance, method_t _method) = 0;

    // [Un]Register handler for availability reporting
    virtual void register_availability_handler(service_t _service,
            instance_t _instance, availability_handler_t _handler) = 0;
    virtual void unregister_availability_handler(service_t _service,
            instance_t _instance) = 0;

    // [Un]Register handler for subscriptions
    virtual void register_subscription_handler(service_t _service,
            instance_t _instance, eventgroup_t _eventgroup,
            subscription_handler_t _handler) = 0;
    virtual void unregister_subscription_handler(service_t _service,
                instance_t _instance, eventgroup_t _eventgroup) = 0;
};

} // namespace vsomeip

#endif // VSOMEIP_APPLICATION_HPP
