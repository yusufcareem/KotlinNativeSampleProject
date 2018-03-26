package com.careem.adma.booking.framework.reducers

import com.careem.adma.booking.framework.NonAction
import com.careem.adma.booking.framework.reducers.ReducerTestUtil.generateDispatchInRideBooking
import com.careem.adma.booking.framework.reducers.ReducerTestUtil.generateLaterBooking
import com.careem.adma.booking.framework.reducers.ReducerTestUtil.generateOnDemandBooking
import com.careem.adma.booking.framework.reducers.ReducerTestUtil.generatePoolingBooking
import com.careem.adma.booking.framework.action.BootstrapAction
import com.careem.adma.booking.framework.models.BookingStoreState
import com.careem.adma.booking.framework.models.asRoute
import com.careem.adma.booking.framework.models.NavigationStop
import com.careem.adma.booking.framework.models.StopType
import kotlin.test.*

class BootstrapReducerTest {

    @Test
    fun `test now only bootstrap`() {
        val bookings = (1..10).map { generateOnDemandBooking(it.toLong()) }
        val action = BootstrapAction(bookings, null)

        val bootstrapReducer = BootstrapReducer()
        val (updatedState, nextAction) = bootstrapReducer.reduce(BookingStoreState(), action)
        assertTrue(nextAction is NonAction)
        assertTrue(updatedState.later.isEmpty())
        assertEquals(updatedState.now.size, 10)
        bookings.forEachIndexed { index, booking ->
            assertEquals(updatedState.now[index], booking.asRoute()) }
        assertEquals(bookings.first().bookingId, updatedState.currentBooking?.bookingId)
    }

    @Test
    fun `test now and later bootstrap`() {
        val nowBookings = (1..10).map { generateOnDemandBooking(it.toLong()) }
        val laterBookings = (1..3).map { generateLaterBooking(1000 + it.toLong()) }

        val bookings = laterBookings + nowBookings
        val action = BootstrapAction(bookings, null)

        val bootstrapReducer = BootstrapReducer()
        val (updatedState, nextAction) = bootstrapReducer.reduce(BookingStoreState(), action)
        assertTrue(nextAction is NonAction)
        assertEquals(updatedState.now.size, 10)
        nowBookings.forEachIndexed { index, booking ->
            assertEquals(updatedState.now[index], booking.asRoute()) }
        assertEquals(updatedState.later.size, 3)
        laterBookings.forEachIndexed { index, booking ->
            assertEquals(updatedState.later[index], booking.asRoute()) }
        assertEquals(nowBookings.first().bookingId, updatedState.currentBooking?.bookingId)
    }

    @Test
    fun `test now and dispatch in ride bootstrap`() {
        val dispatchInRide = (1..10).map { generateDispatchInRideBooking(it.toLong()) }

        val bookings = listOf(generateOnDemandBooking(42)) + dispatchInRide
        val action = BootstrapAction(bookings, null)

        val bootstrapReducer = BootstrapReducer()
        val (updatedState, nextAction) = bootstrapReducer.reduce(BookingStoreState(), action)
        assertTrue(nextAction is NonAction)
        assertEquals(updatedState.now.size, 11)
        bookings.forEachIndexed { index, booking ->
            assertEquals(updatedState.now[index], booking.asRoute()) }
        assertEquals(updatedState.later.size, 0)
        assertFalse(updatedState.now[0].bookings.first().isDispatchInRide)
        assertEquals(updatedState.now.count { it.bookings.first().isDispatchInRide },10)
        assertEquals(bookings.first().bookingId, updatedState.currentBooking?.bookingId)
    }

    @Test
    fun `test pooling bootstrap`() {
        val poolingBookings = (1..10).map { generatePoolingBooking(it.toLong()) }
        val navigationStops =
                // nav stop will be pickup every one, then drop off everyone in order
                poolingBookings.map { NavigationStop(it.bookingId, StopType.PICKUP) } +
                        poolingBookings.map { NavigationStop(it.bookingId, StopType.DROPOFF) }
        val laterBookings = (1..3).map { generateLaterBooking(1000 + it.toLong()) }

        val action = BootstrapAction(laterBookings + poolingBookings, navigationStops)

        val bootstrapReducer = BootstrapReducer()
        val (updatedState, nextAction) = bootstrapReducer.reduce(BookingStoreState(), action)
        assertTrue(nextAction is NonAction)
        assertEquals(updatedState.now.size, 1)
        assertEquals(updatedState.later.size, 3)
        assertTrue(updatedState.now[0].isPooling)
        assertEquals(updatedState.now[0].bookings.size, 10)
        assertEquals(updatedState.now[0].navigationStops.size, 20)
        assertEquals(navigationStops.first().bookingId, updatedState.currentBooking?.bookingId)
        updatedState.later.forEach { assertFalse(it.isPooling)}
    }

    @Test
    fun `test pooling and later bootstrap`() {
        val poolingBookings = (1..10).map { generatePoolingBooking(it.toLong()) }
        val navigationStops =
                // nav stop will be pickup every one, then drop off everyone in order
                poolingBookings.map { NavigationStop(it.bookingId, StopType.PICKUP) } +
                        poolingBookings.map { NavigationStop(it.bookingId, StopType.DROPOFF) }


        val action = BootstrapAction(poolingBookings, navigationStops)

        val bootstrapReducer = BootstrapReducer()
        val (updatedState, nextAction) = bootstrapReducer.reduce(BookingStoreState(), action)
        assertTrue(nextAction is NonAction)
        assertEquals(updatedState.now.size, 1)
        assertEquals(updatedState.later.size, 0)
        assertTrue(updatedState.now[0].isPooling)
        assertEquals(updatedState.now[0].bookings.size, 10)
        assertEquals(navigationStops.first().bookingId, updatedState.currentBooking?.bookingId)
    }

    @Test
    fun `test clear data via bootstrap`() {
        val bookings = (1..10).map { generateOnDemandBooking(it.toLong()) } +
                (1..3).map { generateLaterBooking(10 + it.toLong()) }

        val action = BootstrapAction(emptyList(), null)
        val reducer = BootstrapReducer()
        val (updatedState, nextAction) =
                reducer.reduce(BookingStoreState(now = bookings.map { it.asRoute() },
                        currentBooking = bookings[0]), action)
        assertTrue(nextAction is NonAction)
        assertTrue(updatedState.now.isEmpty())
        assertTrue(updatedState.later.isEmpty())
        assertNull(updatedState.currentBooking)
    }
}