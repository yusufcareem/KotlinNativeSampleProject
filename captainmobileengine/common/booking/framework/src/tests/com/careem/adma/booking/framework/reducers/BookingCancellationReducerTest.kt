package com.careem.adma.booking.framework.reducers

import com.careem.adma.booking.framework.models.Booking
import com.careem.adma.booking.framework.models.BookingStoreState
import com.careem.adma.booking.framework.action.BookingCancelledAction
import com.careem.adma.booking.framework.action.DeleteBookingCommandAction
import com.careem.adma.booking.framework.models.NavigationStop
import com.careem.adma.booking.framework.models.StopType
import kotlin.test.*

class BookingCancellationReducerTest {
    @Test
    fun `test now booking is cancelled`() {
        val booking = Booking()
        val state = BookingStoreState(currentBooking = booking)
        val reducer = BookingCancellationReducer()
        val action = BookingCancelledAction(booking, emptyList())
        val (updatedState, updatedAction) = reducer.doReduce(state, action)
        assertEquals(state, updatedState)
        assertTrue(updatedAction is DeleteBookingCommandAction)
        assertEquals(booking, (updatedAction as DeleteBookingCommandAction).cancelledBooking)
        assertEquals(emptyList<NavigationStop>(), updatedAction.navStops)
        assertTrue(updatedAction.isCurrentBooking)
    }

    @Test
    fun `test later booking is cancelled`() {
        val state = BookingStoreState()
        val booking = Booking()
        val reducer = BookingCancellationReducer()
        val action = BookingCancelledAction(booking, emptyList())
        val (updatedState, updatedAction) = reducer.doReduce(state, action)
        assertEquals(state, updatedState)
        assertTrue(updatedAction is DeleteBookingCommandAction)
        assertEquals(booking, (updatedAction as DeleteBookingCommandAction).cancelledBooking)
        assertEquals(emptyList<NavigationStop>(), updatedAction.navStops)
        assertFalse(updatedAction.isCurrentBooking)
    }

    @Test
    fun `test pooling booking is cancelled`() {
        val booking = Booking()
        val state = BookingStoreState(currentBooking = booking)
        val reducer = BookingCancellationReducer()
        val navigation = listOf<NavigationStop>(
                NavigationStop(bookingId = 1, stopType = StopType.PICKUP),
                NavigationStop(bookingId = 1, stopType = StopType.DROPOFF))
        val action = BookingCancelledAction(booking, navigation)
        val (updatedState, updatedAction) = reducer.doReduce(state, action)
        assertEquals(state, updatedState)
        assertTrue(updatedAction is DeleteBookingCommandAction)
        assertEquals(booking, (updatedAction as DeleteBookingCommandAction).cancelledBooking)
        assertEquals(navigation, updatedAction.navStops)
        assertTrue(updatedAction.isCurrentBooking)
    }

    @Test
    fun `test pooling booking is cancelled when active booking is cancelled`() {
        val booking = Booking()
        val state = BookingStoreState(currentBooking = booking)
        val secondPoolingBooking = Booking(bookingId = 1)
        val reducer = BookingCancellationReducer()
        val navigation = listOf<NavigationStop>(
                NavigationStop(bookingId = 0, stopType = StopType.PICKUP),
                NavigationStop(bookingId = 0, stopType = StopType.DROPOFF))
        val action = BookingCancelledAction(secondPoolingBooking, navigation)
        val (updatedState, updatedAction) = reducer.doReduce(state, action)
        assertEquals(state, updatedState)
        assertTrue(updatedAction is DeleteBookingCommandAction)
        assertEquals(secondPoolingBooking, (updatedAction as DeleteBookingCommandAction).cancelledBooking)
        assertEquals(navigation, updatedAction.navStops)
        assertFalse(updatedAction.isCurrentBooking)
    }

    @Test
    fun `test dispatch in ride booking is cancelled`() {
        val booking = Booking()
        val state = BookingStoreState(currentBooking = booking)
        val dispatchInRideBooking = Booking(bookingId = 1)
        val reducer = BookingCancellationReducer()
        val action = BookingCancelledAction(dispatchInRideBooking, emptyList())
        val (updatedState, updatedAction) = reducer.doReduce(state, action)
        assertEquals(state, updatedState)
        assertTrue(updatedAction is DeleteBookingCommandAction)
        assertEquals(dispatchInRideBooking, (updatedAction as DeleteBookingCommandAction).cancelledBooking)
        assertEquals(emptyList<NavigationStop>(), updatedAction.navStops)
        assertFalse(updatedAction.isCurrentBooking)
    }
}