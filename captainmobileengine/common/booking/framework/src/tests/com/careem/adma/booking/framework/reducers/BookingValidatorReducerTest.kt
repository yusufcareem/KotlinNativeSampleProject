//package com.careem.adma.booking.framework.reducers
//
//import com.careem.adma.booking.framework.models.Booking
//import com.careem.adma.booking.framework.models.BookingStoreState
//import com.careem.adma.booking.framework.models.BookingStatus
//import com.careem.adma.booking.framework.models.BookingType
//import com.careem.adma.booking.framework.action.InsertBookingCommandAction
//import com.careem.adma.booking.framework.action.ConcurrentBookingErrorCommandAction
//import com.careem.adma.booking.framework.action.ValidateBookingAction
//import com.careem.adma.booking.framework.ex
//
//class BookingValidatorReducerTest {
//
//    @Test
//    fun `test pooling dispatch succeeds if pooling`() {
//        val currentBooking = Booking().apply { bookingId = 42
//            bookingStatus = BookingStatus.DRIVER_HERE
//            isPooling = true
//        }
//        val state = BookingStoreState(currentBooking = currentBooking)
//
//        val assignedBooking = Booking().apply {
//            bookingId = 43
//            isPooling = true
//            bookingType = BookingType.ON_DEMAND.code
//            driverPickupTime = Date(System.currentTimeMillis() + 5 * 60 * 1000)
//        }
//        val action = ValidateBookingAction(assignedBooking, null)
//
//        val reducer = BookingValidatorReducer()
//
//        val (updatedState, updatedAction) = reducer.reduce(state, action)
//        assertThat(updatedAction).isInstanceOf(InsertBookingCommandAction::class)
//        assertThat(updatedState).isEqualTo(state)
//    }
//
//    @Test
//    fun `test pooling dispatch fails if not pooling`() {
//        val currentBooking = Booking().apply { bookingId = 42
//            bookingStatus = BookingStatus.DRIVER_HERE }
//        val state = BookingStoreState(currentBooking = currentBooking)
//
//        val assignedBooking = Booking().apply {
//            bookingId = 43
//            isPooling = true
//            bookingType = BookingType.ON_DEMAND.code
//            driverPickupTime = Date(System.currentTimeMillis() + 5 * 60 * 1000)
//        }
//        val action = ValidateBookingAction(assignedBooking, null)
//
//        val reducer = BookingValidatorReducer()
//
//        val (updatedState, updatedAction) = reducer.reduce(state, action)
//        assertThat(updatedAction).isInstanceOf(ConcurrentBookingErrorCommandAction::class.java)
//        assertThat(updatedState).isEqualTo(state)
//    }
//
//    @Test
//    fun `test dispatch in ride passes`() {
//        val currentBooking = Booking().apply { bookingId = 42
//            bookingStatus = BookingStatus.DRIVER_HERE }
//        val state = BookingStoreState(currentBooking = currentBooking,
//                configDoesSupportDispatchInRide = true)
//
//        val assignedBooking = Booking().apply { bookingId = 43
//            isDispatchInRide = true
//            bookingType = BookingType.ON_DEMAND.code
//            driverPickupTime = Date(System.currentTimeMillis() + 5 * 60 * 1000)
//        }
//        val action = ValidateBookingAction(assignedBooking, null)
//
//        val reducer = BookingValidatorReducer()
//
//        val (updatedState, updatedAction) = reducer.reduce(state, action)
//        assertThat(updatedAction).isInstanceOf(InsertBookingCommandAction::class.java)
//        assertThat(updatedState).isEqualTo(state)
//    }
//
//    @Test
//    fun `test dispatch in ride while disabled fails`() {
//        val currentBooking = Booking().apply { bookingId = 42
//            bookingStatus = BookingStatus.DRIVER_HERE }
//        val state = BookingStoreState(currentBooking = currentBooking,
//                configDoesSupportDispatchInRide = false)
//
//        val assignedBooking = Booking().apply { bookingId = 43
//            isDispatchInRide = true
//            bookingType = BookingType.ON_DEMAND.code }
//        val action = ValidateBookingAction(assignedBooking, null)
//
//        val reducer = BookingValidatorReducer()
//
//        val (updatedState, updatedAction) = reducer.reduce(state, action)
//        assertThat(updatedAction).isInstanceOf(ConcurrentBookingErrorCommandAction::class.java)
//        assertThat(updatedState).isEqualTo(state)
//    }
//}