#include "event_bus.h"
#include "stm32f7xx_hal.h"
#include <string.h>

// Event Queue
#define EVENT_QUEUE_SIZE 16

typedef struct {
    event_callback_t callbacks[MAX_SUBSCRIBERS_PER_EVENT];
    uint8_t subscriber_count;
} event_subscriber_list_t;

// Global event subscription table
static event_subscriber_list_t subscriber_table[EVENT_USER_DEFINED_START];

// Event queue for asynchronous processing
static event_t event_queue[EVENT_QUEUE_SIZE];
static uint8_t queue_head = 0;
static uint8_t queue_tail = 0;
static uint8_t queue_count = 0;

/**
 * @brief Initialize the event bus
 */
void event_bus_init(void)
{
    // Clear subscriber table
    memset(subscriber_table, 0, sizeof(subscriber_table));
    
    // Clear event queue
    queue_head = 0;
    queue_tail = 0;
    queue_count = 0;
}

/**
 * @brief Subscribe to an event type
 * @param event_type Type of event to subscribe to
 * @param callback Callback function to call when event occurs
 * @return true if subscription successful, false otherwise
 */
bool event_bus_subscribe(event_type_t event_type, event_callback_t callback)
{
    if (event_type >= EVENT_USER_DEFINED_START || callback == NULL) {
        return false;
    }
    
    event_subscriber_list_t* list = &subscriber_table[event_type];
    
    // Check if already subscribed
    for (uint8_t i = 0; i < list->subscriber_count; i++) {
        if (list->callbacks[i] == callback) {
            return true; // Already subscribed
        }
    }
    
    // Add new subscriber
    if (list->subscriber_count < MAX_SUBSCRIBERS_PER_EVENT) {
        list->callbacks[list->subscriber_count] = callback;
        list->subscriber_count++;
        return true;
    }
    
    return false; // Subscriber list full
}

/**
 * @brief Unsubscribe from an event type
 * @param event_type Type of event to unsubscribe from
 * @param callback Callback function to remove
 * @return true if unsubscription successful, false otherwise
 */
bool event_bus_unsubscribe(event_type_t event_type, event_callback_t callback)
{
    if (event_type >= EVENT_USER_DEFINED_START || callback == NULL) {
        return false;
    }
    
    event_subscriber_list_t* list = &subscriber_table[event_type];
    
    // Find and remove callback
    for (uint8_t i = 0; i < list->subscriber_count; i++) {
        if (list->callbacks[i] == callback) {
            // Shift remaining callbacks down
            for (uint8_t j = i; j < list->subscriber_count - 1; j++) {
                list->callbacks[j] = list->callbacks[j + 1];
            }
            list->subscriber_count--;
            return true;
        }
    }
    
    return false; // Callback not found
}

/**
 * @brief Publish an event to the event bus
 * @param event_type Type of event to publish
 * @param data Pointer to event data (will be copied)
 * @param data_size Size of event data in bytes
 * @return true if event published successfully, false otherwise
 */
bool event_bus_publish(event_type_t event_type, void* data, uint32_t data_size)
{
    if (queue_count >= EVENT_QUEUE_SIZE) {
        return false; // Queue full
    }
    
    // Add event to queue
    event_t* event = &event_queue[queue_tail];
    event->type = event_type;
    event->data = data;
    event->data_size = data_size;
    event->timestamp = event_bus_get_tick();
    
    queue_tail = (queue_tail + 1) % EVENT_QUEUE_SIZE;
    queue_count++;
    
    return true;
}

/**
 * @brief Process pending events in the queue
 * 
 * This should be called periodically from the main loop or RTOS task
 */
void event_bus_process(void)
{
    while (queue_count > 0) {
        // Get next event from queue
        event_t* event = &event_queue[queue_head];
        
        // Notify all subscribers
        if (event->type < EVENT_USER_DEFINED_START) {
            event_subscriber_list_t* list = &subscriber_table[event->type];
            
            for (uint8_t i = 0; i < list->subscriber_count; i++) {
                if (list->callbacks[i] != NULL) {
                    list->callbacks[i](event);
                }
            }
        }
        
        // Move to next event
        queue_head = (queue_head + 1) % EVENT_QUEUE_SIZE;
        queue_count--;
    }
}

/**
 * @brief Get current system tick for timestamp
 * @return Current tick count
 */
uint32_t event_bus_get_tick(void)
{
    return HAL_GetTick();
}
