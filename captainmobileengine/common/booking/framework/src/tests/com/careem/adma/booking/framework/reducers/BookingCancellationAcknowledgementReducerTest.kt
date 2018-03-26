package com.careem.adma.booking.framework.reducers

import com.careem.adma.booking.framework.NonAction
import com.careem.adma.booking.framework.models.Booking
import com.careem.adma.booking.framework.models.BookingStoreState
import com.careem.adma.booking.framework.action.BookingCancellationAcknowledgeAction

import kotlin.test.*

internal class BookingCancellationAcknowledgementReducerTest {
    @Test
    fun `test cancellation acknowledgement when booking is present`() {
        val bookingId = 123L
        val booking = Booking(bookingId = bookingId)
        val state = BookingStoreState(cancelledBookings = listOf(booking))
        val reducer = BookingCancellationAcknowledgementReducer()
        val action = BookingCancellationAcknowledgeAction(bookingId)
        val (updatedState, updatedAction)  = reducer.doReduce(state, action)
        assertTrue(updatedAction is NonAction)
        assertEquals(state.copy(cancelledBookings = emptyList()), updatedState)
    }

    @Test
    fun `test cancellation acknowledgement when booking is not present`() {
        val bookingId = 123L
        val state = BookingStoreState(cancelledBookings = emptyList())
        val reducer = BookingCancellationAcknowledgementReducer()
        val action = BookingCancellationAcknowledgeAction(bookingId)
        val (updatedState, updatedAction)  = reducer.doReduce(state, action)
        assertTrue(updatedAction is NonAction)
        assertEquals(state, updatedState)
    }
}