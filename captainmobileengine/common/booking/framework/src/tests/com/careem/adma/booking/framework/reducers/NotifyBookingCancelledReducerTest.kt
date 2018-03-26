package com.careem.adma.booking.framework.reducers

import com.careem.adma.booking.framework.NonAction
import com.careem.adma.booking.framework.models.Booking
import com.careem.adma.booking.framework.models.BookingStoreState
import com.careem.adma.booking.framework.models.NavigationStop
import com.careem.adma.booking.framework.models.StopType
import com.careem.adma.booking.framework.models.Route
import com.careem.adma.booking.framework.action.NotifyBookingCancelledAction
import kotlin.test.*

class NotifyBookingCancelledReducerTest {
    @Test
    fun `test now booking is cancelled`() {
        val booking = Booking()
        val state = BookingStoreState(now = emptyList(), currentBooking = booking)
        val reducer = NotifyBookingCancelledReducer()
        val action = NotifyBookingCancelledAction(booking)
        val (updatedState, updatedAction) = reducer.doReduce(state, action)
        assertEquals(BookingStoreState(currentBooking = null, cancelledBookings = listOf(booking)),
                updatedState)
        assertTrue(updatedAction is NonAction)
    }

    @Test
    fun `test now booking is cancelled with a later booking`() {
        val booking = Booking()
        val laterBooking = Booking(bookingId = 1)
        val laterBookingRoute = Route(bookings = setOf(laterBooking), navigationStops =
        listOf(NavigationStop(bookingId = 1, stopType = StopType.PICKUP),
                NavigationStop(bookingId = 1, stopType = StopType.DROPOFF)))
        val state = BookingStoreState(now = emptyList(),
                later = listOf(laterBookingRoute), currentBooking = booking)
        val reducer = NotifyBookingCancelledReducer()
        val action = NotifyBookingCancelledAction(booking)
        val (updatedState, updatedAction) = reducer.doReduce(state, action)
        assertEquals(BookingStoreState(currentBooking = null,
                later = listOf(laterBookingRoute), cancelledBookings = listOf(booking)),
                updatedState)
        assertTrue(updatedAction is NonAction)
    }

    @Test
    fun `test later booking is cancelled`() {
        val booking = Booking()
        val state = BookingStoreState(later = emptyList(), currentBooking = booking)
        val reducer = NotifyBookingCancelledReducer()
        val action = NotifyBookingCancelledAction(booking)
        val (updatedState, updatedAction) = reducer.doReduce(state, action)
        assertEquals(BookingStoreState(currentBooking = null, cancelledBookings = listOf(booking)),
                updatedState)
        assertTrue(updatedAction is NonAction)
    }

    @Test
    fun `test later booking is cancelled with a now booking`() {
        val laterBooking = Booking()
        val nowBooking = Booking(bookingId = 1)
        val updatedNowRoute = Route(bookings = setOf(nowBooking), navigationStops =
        listOf(NavigationStop(bookingId = 1, stopType = StopType.PICKUP),
                NavigationStop(bookingId = 1, stopType = StopType.DROPOFF)))
        val state = BookingStoreState(later = emptyList(),
                now = listOf(updatedNowRoute), currentBooking = nowBooking)
        val reducer = NotifyBookingCancelledReducer()
        val action = NotifyBookingCancelledAction(laterBooking)
        val (updatedState, updatedAction) = reducer.doReduce(state, action)
        assertEquals(BookingStoreState(currentBooking = nowBooking,
                now = listOf(updatedNowRoute), cancelledBookings = listOf(laterBooking)),
                updatedState)
        assertTrue(updatedAction is NonAction)
    }

    @Test
    fun `test first pooling booking is cancelled`() {
        val firstPoolingBooking = Booking()
        val secondPoolingBooking = Booking(bookingId = 1)
        val updatePoolingRoute = Route(bookings = setOf(secondPoolingBooking), navigationStops =
        listOf(NavigationStop(bookingId = 1, stopType = StopType.PICKUP),
                NavigationStop(bookingId = 1, stopType = StopType.DROPOFF)), isPooling = true)
        val state = BookingStoreState(later = emptyList(),
                now = listOf(updatePoolingRoute), currentBooking = firstPoolingBooking)
        val reducer = NotifyBookingCancelledReducer()
        val action = NotifyBookingCancelledAction(firstPoolingBooking)
        val (updatedState, updatedAction) = reducer.doReduce(state, action)
        assertEquals(BookingStoreState(currentBooking = secondPoolingBooking,
                now = listOf(updatePoolingRoute), cancelledBookings = listOf(firstPoolingBooking)),
                updatedState)
        assertTrue(updatedAction is NonAction)
    }

    @Test
    fun `test second pooling booking is cancelled`() {
        val secondPoolingBooking = Booking()
        val firstPoolingBooking = Booking(bookingId = 1)
        val updatePoolingRoute = Route(bookings = setOf(firstPoolingBooking), navigationStops =
        listOf(NavigationStop(bookingId = 1, stopType = StopType.PICKUP),
                NavigationStop(bookingId = 1, stopType = StopType.DROPOFF)), isPooling = true)
        val state = BookingStoreState(later = emptyList(),
                now = listOf(updatePoolingRoute), currentBooking = firstPoolingBooking)
        val reducer = NotifyBookingCancelledReducer()
        val action = NotifyBookingCancelledAction(secondPoolingBooking)
        val (updatedState, updatedAction) = reducer.doReduce(state, action)
        assertEquals(BookingStoreState(currentBooking = firstPoolingBooking,
                now = listOf(updatePoolingRoute), cancelledBookings = listOf(secondPoolingBooking)),
                updatedState)
        assertTrue(updatedAction is NonAction)
    }
}