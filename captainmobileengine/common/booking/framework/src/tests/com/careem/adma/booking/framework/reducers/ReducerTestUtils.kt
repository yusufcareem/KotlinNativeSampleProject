package com.careem.adma.booking.framework.reducers

import com.careem.adma.booking.framework.models.Booking
import com.careem.adma.booking.framework.models.BookingType
import com.careem.adma.booking.framework.models.BookingStatus

object ReducerTestUtil {

    fun generateOnDemandBooking(id: Long) =
            Booking(bookingId = id,
                    bookingType = BookingType.ON_DEMAND.code,
                    bookingStatus = BookingStatus.DRIVER_ASSIGNED)

    fun generateDispatchInRideBooking(id: Long) =
            Booking(bookingId = id,
                    bookingType = BookingType.ON_DEMAND.code,
                    isDispatchInRide = true,
                    bookingStatus = BookingStatus.DRIVER_ASSIGNED)

    fun generateLaterBooking(id: Long) =
            Booking(bookingId = id,
                    bookingType = BookingType.NORMAL.code,
                    bookingStatus = BookingStatus.DRIVER_ASSIGNED)

    fun generatePoolingBooking(id: Long) =
            Booking(bookingId = id,
                    bookingType = BookingType.ON_DEMAND.code,
                    isPooling = true,
                    bookingStatus = BookingStatus.DRIVER_ASSIGNED)
}
