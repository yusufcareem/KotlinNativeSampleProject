#import <Foundation/Foundation.h>

@class CMEAction, CMECommand, CMENonAction, CMEReducer, CMEStdlibPair, CMEState, CMEStateChange, CMEStdlibException, CMEBookingStoreState, CMEBookingStoreWrapper, CMEBooking, CMENavigationStop, CMEStore, CMEStdlibUnit, CMETestGenerics, CMEBookingStatus, CMEStdlibEnum, CMEBookingStatusCompanion, CMERoute, CMEStateError, CMEBookingStateStoreConstants, CMEBookingType, CMEBookingTypeCompanion, CMECityConfigConstants, CMEStopType, CMEStopTypeCompanion, CMEBookingCancelledAction, CMEStdlibThrowable;

@protocol CMEDispatcher, CMEObservable, CMELogManager, CMEStoreInterface, CMEStoreListener, CMEBookingStoreListener, CMEStdlibKClass, CMEBehaviorSubjectProvider, CMEBehaviorSubject, CMEScheduler, CMEObservableProvider, CMESchedulerProvider, CMESingle, CMELocationModel, CMEStdlibComparable, CMECityConfigurationModel, CMEStdlibKDeclarationContainer, CMEStdlibKAnnotatedElement, CMEStdlibKClassifier;

NS_ASSUME_NONNULL_BEGIN

@interface KotlinBase : NSObject
-(instancetype) init __attribute__((unavailable));
+(instancetype) new __attribute__((unavailable));
+(void)initialize __attribute__((objc_requires_super));
@end;

@interface KotlinBase (KotlinBaseCopying) <NSCopying>
@end;

__attribute__((objc_runtime_name("KotlinMutableSet")))
@interface CMEMutableSet<ObjectType> : NSMutableSet<ObjectType>
@end;

__attribute__((objc_runtime_name("KotlinMutableDictionary")))
@interface CMEMutableDictionary<KeyType, ObjectType> : NSMutableDictionary<KeyType, ObjectType>
@end;

@interface CMEAction : KotlinBase
-(instancetype)init NS_SWIFT_NAME(init()) NS_DESIGNATED_INITIALIZER;

@end;

@interface CMECommand : KotlinBase
-(instancetype)init NS_SWIFT_NAME(init()) NS_DESIGNATED_INITIALIZER;

-(CMEAction*)doExecuteAction:(CMEAction*)action NS_SWIFT_NAME(doExecute(action:));
-(CMEAction*)executeAction:(CMEAction*)action NS_SWIFT_NAME(execute(action:));
@end;

@protocol CMEDispatcher
@required
@property (readonly) id<CMEObservable> actions;
@end;

__attribute__((objc_subclassing_restricted))
@interface CMENonAction : CMEAction
-(instancetype)init NS_SWIFT_NAME(init()) NS_DESIGNATED_INITIALIZER;

@end;

@interface CMEReducer : KotlinBase
-(instancetype)init NS_SWIFT_NAME(init()) NS_DESIGNATED_INITIALIZER;

-(CMEStdlibPair*)doReduceState:(CMEState*)state action:(CMEAction*)action NS_SWIFT_NAME(doReduce(state:action:));
-(CMEStdlibPair*)reduceState:(CMEState*)state action:(CMEAction*)action NS_SWIFT_NAME(reduce(state:action:));
@end;

@interface CMEState : KotlinBase
-(instancetype)init NS_SWIFT_NAME(init()) NS_DESIGNATED_INITIALIZER;

@end;

__attribute__((objc_subclassing_restricted))
@interface CMEStateChange : KotlinBase
-(instancetype)initWithOldState:(id _Nullable)oldState newState:(id _Nullable)newState NS_SWIFT_NAME(init(oldState:newState:)) NS_DESIGNATED_INITIALIZER;

-(id _Nullable)component1 NS_SWIFT_NAME(component1());
-(id _Nullable)component2 NS_SWIFT_NAME(component2());
-(CMEStateChange*)doCopyOldState:(id _Nullable)oldState newState:(id _Nullable)newState NS_SWIFT_NAME(doCopy(oldState:newState:));
@property (readonly) id _Nullable oldState;
@property (getter=doNewState, readonly) id _Nullable newState;
@end;

@protocol CMELogManager
@required
-(void)logMessage:(NSString*)message NS_SWIFT_NAME(log(message:));
-(void)logException:(CMEStdlibException*)exception NS_SWIFT_NAME(log(exception:));
@end;

@protocol CMEStoreInterface
@required
-(CMEAction*)dispatchAction:(CMEAction*)action NS_SWIFT_NAME(dispatch(action:));
@end;

@protocol CMEStoreListener
@required
-(void)notifyOnStateChangedStateChange:(CMEStateChange*)stateChange NS_SWIFT_NAME(notifyOnStateChanged(stateChange:));
@end;

@protocol CMEBookingStoreListener
@required
-(void)bookingStoreUpdatedBookingStoreState:(CMEBookingStoreState*)bookingStoreState NS_SWIFT_NAME(bookingStoreUpdated(bookingStoreState:));
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEBookingStoreWrapper : KotlinBase <CMEStoreListener>
-(instancetype)init NS_SWIFT_NAME(init()) NS_DESIGNATED_INITIALIZER;

-(void)onMyWayBookingId:(int64_t)bookingId NS_SWIFT_NAME(onMyWay(bookingId:));
-(void)onBookingAddedBooking:(CMEBooking*)booking navStops:(NSArray<CMENavigationStop*>* _Nullable)navStops NS_SWIFT_NAME(onBookingAdded(booking:navStops:));
-(void)onArrivedForPickupBookingId:(int64_t)bookingId NS_SWIFT_NAME(onArrivedForPickup(bookingId:));
-(void)validateBooking:(CMEBooking*)booking navStops:(NSArray<CMENavigationStop*>* _Nullable)navStops NS_SWIFT_NAME(validate(booking:navStops:));
@property id<CMEBookingStoreListener> _Nullable delegate;
@property (readonly) CMEStore* store;
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEStore : KotlinBase
-(instancetype)initWithState:(CMEState*)state reducers:(NSDictionary<id<CMEStdlibKClass>, CMEReducer*>*)reducers delegate:(id<CMEStoreListener>)delegate NS_SWIFT_NAME(init(state:reducers:delegate:)) NS_DESIGNATED_INITIALIZER;

-(void)dispatchAction:(CMEAction*)action NS_SWIFT_NAME(dispatch(action:));
-(void)notifyOnStateChangedStateChange:(CMEStateChange*)stateChange NS_SWIFT_NAME(notifyOnStateChanged(stateChange:));
@end;

@protocol CMEBehaviorSubjectProvider
@required
-(id<CMEBehaviorSubject>)create NS_SWIFT_NAME(create());
@end;

@protocol CMEObservable
@required
-(void)subscribe NS_SWIFT_NAME(subscribe());
-(void)subscribeCallback:(CMEStdlibUnit*(^)(id _Nullable))callback NS_SWIFT_NAME(subscribe(callback:));
-(id<CMEObservable>)subscribeOnOn:(id<CMEScheduler>)on NS_SWIFT_NAME(subscribeOn(on:));
@end;

@protocol CMEBehaviorSubject <CMEObservable>
@required
-(id<CMEBehaviorSubject>)toSerialized NS_SWIFT_NAME(toSerialized());
-(void)onNextOnNext:(id _Nullable)onNext NS_SWIFT_NAME(onNext(onNext:));
-(id<CMEBehaviorSubject>)doOnNextOnNext:(CMEStdlibUnit*(^)(id _Nullable))onNext NS_SWIFT_NAME(doOnNext(onNext:));
@end;

__attribute__((objc_subclassing_restricted))
@interface CMETestGenerics : KotlinBase
-(instancetype)init NS_SWIFT_NAME(init()) NS_DESIGNATED_INITIALIZER;

-(void)testType:(id)type NS_SWIFT_NAME(test(type:));
@end;

@protocol CMEObservableProvider
@required
-(id<CMEObservable>)mergeList:(id)list NS_SWIFT_NAME(merge(list:));
@end;

@protocol CMEScheduler
@required
@end;

@protocol CMESchedulerProvider
@required
-(id<CMEScheduler>)io NS_SWIFT_NAME(io());
@end;

@protocol CMESingle
@required
-(void)subscribeCallback_:(CMEStdlibUnit*(^)(id _Nullable))callback NS_SWIFT_NAME(subscribe(callback_:));
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEBooking : KotlinBase
-(instancetype)initWithBooking:(CMEBooking*)booking NS_SWIFT_NAME(init(booking:)) NS_DESIGNATED_INITIALIZER;

-(instancetype)initWithBookingId:(int64_t)bookingId bookingStatus:(CMEBookingStatus*)bookingStatus isOnDemandBooking:(BOOL)isOnDemandBooking isValid:(BOOL)isValid isDispatchInRide:(BOOL)isDispatchInRide bookingType:(int32_t)bookingType isPooling:(BOOL)isPooling NS_SWIFT_NAME(init(bookingId:bookingStatus:isOnDemandBooking:isValid:isDispatchInRide:bookingType:isPooling:)) NS_DESIGNATED_INITIALIZER;

-(BOOL)isPoolingCompatibleBooking:(CMEBooking*)booking NS_SWIFT_NAME(isPoolingCompatible(booking:));
-(void)removeBookingByADMASpecificDropOff NS_SWIFT_NAME(removeBookingByADMASpecificDropOff());
-(void)updateBookingByADMASpecificDropOffLocationModel:(id<CMELocationModel>)locationModel NS_SWIFT_NAME(updateBookingByADMASpecificDropOff(locationModel:));
-(int64_t)component1 NS_SWIFT_NAME(component1());
-(CMEBookingStatus*)component2 NS_SWIFT_NAME(component2());
-(BOOL)component3 NS_SWIFT_NAME(component3());
-(BOOL)component4 NS_SWIFT_NAME(component4());
-(BOOL)component5 NS_SWIFT_NAME(component5());
-(int32_t)component6 NS_SWIFT_NAME(component6());
-(BOOL)component7 NS_SWIFT_NAME(component7());
-(CMEBooking*)doCopyBookingId:(int64_t)bookingId bookingStatus:(CMEBookingStatus*)bookingStatus isOnDemandBooking:(BOOL)isOnDemandBooking isValid:(BOOL)isValid isDispatchInRide:(BOOL)isDispatchInRide bookingType:(int32_t)bookingType isPooling:(BOOL)isPooling NS_SWIFT_NAME(doCopy(bookingId:bookingStatus:isOnDemandBooking:isValid:isDispatchInRide:bookingType:isPooling:));
@property (readonly) int64_t bookingId;
@property CMEBookingStatus* bookingStatus;
@property (readonly) BOOL isOnDemandBooking;
@property (readonly) BOOL isValid;
@property (readonly) BOOL isDispatchInRide;
@property (readonly) int32_t bookingType;
@property (readonly) BOOL isPooling;
@end;

@protocol CMEStdlibComparable
@required
-(int32_t)compareToOther:(id _Nullable)other NS_SWIFT_NAME(compareTo(other:));
@end;

@interface CMEStdlibEnum : KotlinBase <CMEStdlibComparable>
-(instancetype)initWithName:(NSString*)name ordinal:(int32_t)ordinal NS_SWIFT_NAME(init(name:ordinal:)) NS_DESIGNATED_INITIALIZER;

-(id)clone NS_SWIFT_NAME(clone());
-(int32_t)compareToOther:(CMEStdlibEnum*)other NS_SWIFT_NAME(compareTo(other:));
@property (readonly) NSString* name;
@property (readonly) int32_t ordinal;
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEBookingStatus : CMEStdlibEnum
+(instancetype)alloc __attribute__((unavailable));
+(instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));

@property (class, readonly) CMEBookingStatus* upcoming;
@property (class, readonly) CMEBookingStatus* driverAssigned;
@property (class, readonly) CMEBookingStatus* driverComing;
@property (class, readonly) CMEBookingStatus* driverHere;
@property (class, readonly) CMEBookingStatus* tripStarted;
@property (class, readonly) CMEBookingStatus* tripEnded;
@property (class, readonly) CMEBookingStatus* canceled;
@property (class, readonly) CMEBookingStatus* rejectedDueToCapacity;
@property (class, readonly) CMEBookingStatus* rejectedDueToBlackOut;
@property (class, readonly) CMEBookingStatus* multiStopWayPointDeparture;
@property (class, readonly) CMEBookingStatus* multiStopWayPointArrival;

-(instancetype)initWithName:(NSString*)name ordinal:(int32_t)ordinal NS_SWIFT_NAME(init(name:ordinal:)) NS_DESIGNATED_INITIALIZER __attribute__((unavailable));

-(int32_t)compareToOther:(CMEBookingStatus*)other NS_SWIFT_NAME(compareTo(other:));
@property (readonly) int32_t code;
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEBookingStatusCompanion : KotlinBase
+(instancetype)alloc __attribute__((unavailable));
+(instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));

+(instancetype)companion NS_SWIFT_NAME(init());

-(CMEBookingStatus* _Nullable)fromCodeCode:(int32_t)code NS_SWIFT_NAME(fromCode(code:));
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEBookingStoreState : CMEState
-(instancetype)initWithNow:(NSArray<CMERoute*>*)now later:(NSArray<CMERoute*>*)later currentBooking:(CMEBooking* _Nullable)currentBooking lastAssignedBooking:(CMEBooking* _Nullable)lastAssignedBooking cancelledBookings:(NSArray<CMEBooking*>*)cancelledBookings configDoesSupportDispatchInRide:(BOOL)configDoesSupportDispatchInRide configOnDemandPickupTimeValidity:(int32_t)configOnDemandPickupTimeValidity configDangerPeriodBasedOnSLA:(NSDictionary<NSString*, NSNumber*>*)configDangerPeriodBasedOnSLA configInsideDangerPeriodBasedOnSLA:(NSDictionary<NSString*, NSNumber*>*)configInsideDangerPeriodBasedOnSLA configOutsideDangerPeriodBasedOnSLA:(NSDictionary<NSString*, NSNumber*>*)configOutsideDangerPeriodBasedOnSLA errorState:(NSSet<CMEStateError*>*)errorState NS_SWIFT_NAME(init(now:later:currentBooking:lastAssignedBooking:cancelledBookings:configDoesSupportDispatchInRide:configOnDemandPickupTimeValidity:configDangerPeriodBasedOnSLA:configInsideDangerPeriodBasedOnSLA:configOutsideDangerPeriodBasedOnSLA:errorState:)) NS_DESIGNATED_INITIALIZER;

-(instancetype)init NS_SWIFT_NAME(init()) NS_DESIGNATED_INITIALIZER __attribute__((unavailable));

-(CMEBookingStoreState*)initialState NS_SWIFT_NAME(initialState());
-(NSArray<CMERoute*>*)component1 NS_SWIFT_NAME(component1());
-(NSArray<CMERoute*>*)component2 NS_SWIFT_NAME(component2());
-(CMEBooking* _Nullable)component3 NS_SWIFT_NAME(component3());
-(CMEBooking* _Nullable)component4 NS_SWIFT_NAME(component4());
-(NSArray<CMEBooking*>*)component5 NS_SWIFT_NAME(component5());
-(BOOL)component6 NS_SWIFT_NAME(component6());
-(int32_t)component7 NS_SWIFT_NAME(component7());
-(NSDictionary<NSString*, NSNumber*>*)component8 NS_SWIFT_NAME(component8());
-(NSDictionary<NSString*, NSNumber*>*)component9 NS_SWIFT_NAME(component9());
-(NSDictionary<NSString*, NSNumber*>*)component10 NS_SWIFT_NAME(component10());
-(NSSet<CMEStateError*>*)component11 NS_SWIFT_NAME(component11());
-(CMEBookingStoreState*)doCopyNow:(NSArray<CMERoute*>*)now later:(NSArray<CMERoute*>*)later currentBooking:(CMEBooking* _Nullable)currentBooking lastAssignedBooking:(CMEBooking* _Nullable)lastAssignedBooking cancelledBookings:(NSArray<CMEBooking*>*)cancelledBookings configDoesSupportDispatchInRide:(BOOL)configDoesSupportDispatchInRide configOnDemandPickupTimeValidity:(int32_t)configOnDemandPickupTimeValidity configDangerPeriodBasedOnSLA:(NSDictionary<NSString*, NSNumber*>*)configDangerPeriodBasedOnSLA configInsideDangerPeriodBasedOnSLA:(NSDictionary<NSString*, NSNumber*>*)configInsideDangerPeriodBasedOnSLA configOutsideDangerPeriodBasedOnSLA:(NSDictionary<NSString*, NSNumber*>*)configOutsideDangerPeriodBasedOnSLA errorState:(NSSet<CMEStateError*>*)errorState NS_SWIFT_NAME(doCopy(now:later:currentBooking:lastAssignedBooking:cancelledBookings:configDoesSupportDispatchInRide:configOnDemandPickupTimeValidity:configDangerPeriodBasedOnSLA:configInsideDangerPeriodBasedOnSLA:configOutsideDangerPeriodBasedOnSLA:errorState:));
@property (readonly) NSArray<CMERoute*>* now;
@property (readonly) NSArray<CMERoute*>* later;
@property (readonly) CMEBooking* _Nullable currentBooking;
@property (readonly) CMEBooking* _Nullable lastAssignedBooking;
@property (readonly) NSArray<CMEBooking*>* cancelledBookings;
@property (readonly) BOOL configDoesSupportDispatchInRide;
@property (readonly) int32_t configOnDemandPickupTimeValidity;
@property (readonly) NSDictionary<NSString*, NSNumber*>* configDangerPeriodBasedOnSLA;
@property (readonly) NSDictionary<NSString*, NSNumber*>* configInsideDangerPeriodBasedOnSLA;
@property (readonly) NSDictionary<NSString*, NSNumber*>* configOutsideDangerPeriodBasedOnSLA;
@property (readonly) NSSet<CMEStateError*>* errorState;
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEBookingStateStoreConstants : KotlinBase
+(instancetype)alloc __attribute__((unavailable));
+(instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));

+(instancetype)bookingStateStoreConstants NS_SWIFT_NAME(init());

@property (readonly) NSString* SLA_NORMAL;
@property (readonly) NSString* SLA_CORPORATE;
@property (readonly) NSString* SLA_VIP;
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEBookingType : CMEStdlibEnum
+(instancetype)alloc __attribute__((unavailable));
+(instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));

@property (class, readonly) CMEBookingType* normal;
@property (class, readonly) CMEBookingType* onDemand;
@property (class, readonly) CMEBookingType* unconfirmed;
@property (class, readonly) CMEBookingType* walkIn;

-(instancetype)initWithName:(NSString*)name ordinal:(int32_t)ordinal NS_SWIFT_NAME(init(name:ordinal:)) NS_DESIGNATED_INITIALIZER __attribute__((unavailable));

-(int32_t)compareToOther:(CMEBookingType*)other NS_SWIFT_NAME(compareTo(other:));
@property (readonly) int32_t code;
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEBookingTypeCompanion : KotlinBase
+(instancetype)alloc __attribute__((unavailable));
+(instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));

+(instancetype)companion NS_SWIFT_NAME(init());

-(CMEBookingType* _Nullable)fromCodeCode:(int32_t)code NS_SWIFT_NAME(fromCode(code:));
@end;

__attribute__((objc_subclassing_restricted))
@interface CMECityConfigConstants : KotlinBase
+(instancetype)alloc __attribute__((unavailable));
+(instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));

+(instancetype)cityConfigConstants NS_SWIFT_NAME(init());

@property (readonly) NSString* CITY_CONFIG_URL;
@property (readonly) NSString* MAX_AMOUNT_PER_CITY;
@property (readonly) NSString* MAX_EXTRA_CASH_AMOUNT_PER_CITY;
@property (readonly) NSString* MAX_SURCHARGE_PER_CITY;
@property (readonly) NSString* ZONE_INFORMATION_UPDATE_INTERVAL;
@property (readonly) NSString* ENABLE_TRAFFIC_TOGGLE;
@property (readonly) NSString* BACK_OUT_DANGER_PERIOD_NORMAL;
@property (readonly) NSString* BACK_OUT_DANGER_PERIOD_CORPORATE;
@property (readonly) NSString* BACK_OUT_DANGER_PERIOD_VIP;
@property (readonly) NSString* BACK_OUT_PENALTY_OUTSIDE_DANGER_PERIOD_NORMAL;
@property (readonly) NSString* BACK_OUT_PENALTY_OUTSIDE_DANGER_PERIOD_CORPORATE;
@property (readonly) NSString* BACK_OUT_PENALTY_OUTSIDE_DANGER_PERIOD_VIP;
@property (readonly) NSString* BACK_OUT_PENALTY_INSIDE_DANGER_PERIOD_NORMAL;
@property (readonly) NSString* BACK_OUT_PENALTY_INSIDE_DANGER_PERIOD_CORPORATE;
@property (readonly) NSString* BACK_OUT_PENALTY_INSIDE_DANGER_PERIOD_VIP;
@property (readonly) NSString* ENABLE_PICKUP_TRANSLATION;
@property (readonly) NSString* ENABLE_DRIVER_NOTES_TRANSLATION;
@property (readonly) NSString* ENABLE_WAYPOINT_TRANSLATION;
@property (readonly) NSString* ENABLE_DROPOFF_TRANSLATION;
@property (readonly) NSString* DISABLE_DROPOFF_LOCATION_VISIBILITY_ON_NOW_DISPATCH;
@property (readonly) NSString* DISABLE_DROPOFF_LOCATION_VISIBILITY_ON_LATER_DISPATCH;
@property (readonly) NSString* ENABLE_WAZE_NAVIGATION;
@property (readonly) NSString* ENABLE_YANDEX_NAVIGATION;
@property (readonly) NSString* DRIVER_AVAILABLE_PING_FREQUENCY;
@property (readonly) NSString* DRIVER_OFFLINE_PING_FREQUENCY;
@property (readonly) NSString* DRIVER_COMING_PING_FREQUENCY;
@property (readonly) NSString* DRIVER_WAITING_PING_FREQUENCY;
@property (readonly) NSString* DRIVER_IN_RIDE_PING_FREQUENCY;
@property (readonly) NSString* LOST_OFFER_CHECK_SERVICE_INTERVAL_MILLIS;
@property (readonly) NSString* LOST_OFFER_RE_REGISTER_THRESHOLD;
@property (readonly) NSString* DISPATCH_TIME_THRESHOLD_FOR_BUSY_DRIVERS;
@property (readonly) NSString* DISTANCE_TO_PICKUP_LATER_BOOKING_ENABLE_THRESHOLD_MINS;
@property (readonly) NSString* NOW_BOOKING_PICKUP_TIME_VALIDITY_THRESHOLD_IN_MINS;
@property (readonly) NSString* DISABLE_CUSTOMER_WANTS_TO_CANCEL;
@property (readonly) NSString* CUSTOMER_RATING_ENABLED;
@property (readonly) NSString* FUSED_LOCATION_UPDATES_FREQUENCY_SEC_IN_FREE_MODE;
@property (readonly) NSString* FUSED_LOCATION_UPDATES_FREQUENCY_SEC_IN_BUSY_MODE;
@property (readonly) NSString* SHOW_PRICING_TYPE_IN_CASH_RECEIPT;
@property (readonly) NSString* ENABLE_SQS_HANDLER;
@property (readonly) NSString* DRIVER_PROFILE_ENABLED;
@property (readonly) NSString* BOOKING_OFFER_NETWORK_DELAY_BUFFER;
@property (readonly) int32_t NO_VALUE;
@property (readonly) int32_t DEFAULT_LOST_OFFER_RE_REGISTER_THRESHOLD;
@property (readonly) int64_t DEFAULT_LOST_OFFERS_CHECK_INTERVAL_MILLIS;
@property (readonly) int32_t ONE_MIN_IN_MILLIS;
@property (readonly) int64_t DEFAULT_BOOKING_OFFER_EVENT_REPORTING_INTERVAL_MILLIS;
@property (readonly) int32_t DEFAULT_ZONE_INFORMATION_UPDATE_INTERVAL;
@property (readonly) NSString* BOOKING_OFFER_EVENT_REPORTING_INTERVAL;
@property (readonly) int32_t DEFAULT_LAST_CAPTAIN_RATINGS_COUNT;
@property (readonly) int32_t DEFAULT_CAPTAIN_MIN_DISPLAY_RATINGS;
@property (readonly) int32_t DEFAULT_DISPUTE_RESPONSE_ETA_IN_HOURS;
@property (readonly) int32_t DEFAULT_DISTANCE_TO_PICKUP_LATER_BOOKING_ENABLE_THRESHOLD_MINS;
@property (readonly) int32_t DEFAULT_DISPATCH_TIME_THRESHOLD_FOR_BUSY_DRIVERS;
@property (readonly) int64_t BOOKING_OFFER_NETWORK_DELAY_BUFFER_DEFAULT;
@property (readonly) int32_t DEFAULT_NOW_BOOKING_PICKUP_TIME_VALIDITY_THRESHOLD_IN_MINS;
@property (readonly) NSString* ENABLE_CAPTAIN_PORTAL;
@property (readonly) NSString* DISABLE_CASH_LABEL_DISPLAY;
@property (readonly) NSString* ENABLE_CAPTAIN_DISPUTE_SUPPORT;
@property (readonly) NSString* ENABLE_CAPTAIN_DISPUTE_INBOX;
@property (readonly) NSString* CAPTAIN_DISPUTES;
@property (readonly) NSString* SHOW_CAR_TYPE_IN_OFFER;
@property (readonly) NSString* DISABLE_MOCK_LOCATIONS;
@property (readonly) NSString* ENABLE_REFRESH_TOKEN;
@property (readonly) NSString* ENABLE_MOBILE_DATA_OFF_EVENT;
@property (readonly) NSString* DISABLE_ROUTE_DRAWING;
@property (readonly) NSString* CAPTAIN_ALLOWED_TO_SKIP_UPDATE;
@property (readonly) NSString* ENABLE_HEAT_MAP;
@property (readonly) NSString* AUTO_ACCEPT_BOOKINGS;
@property (readonly) NSString* DISABLE_BOOKING_STATUS_SYNC;
@property (readonly) NSString* ENABLE_ONE_CARD_PAYMENT_OPTION;
@property (readonly) NSString* REFERRED_DRIVER_TRIPS_TARGET_COUNT;
@property (readonly) NSString* REFERRING_DRIVER_TRIPS_TARGET_REWARD_AMOUNT;
@property (readonly) NSString* DRIVER_REFERRED_DRIVER_REWARD_EXPIRY_PERIOD_IN_DAYS;
@property (readonly) NSString* DISABLE_CAPTAIN_REFERRAL;
@property (readonly) NSString* DRIVER_REFERRED_DRIVER_PROGRAM_TYPE;
@property (readonly) NSString* DISABLE_DISPATCH_CONFIRMATION_DIALOG;
@property (readonly) NSString* HIDE_CAPTAIN_PORTAL_CLOSE_BUTTON;
@property (readonly) NSString* ENABLE_DESTINATION_FILTER_BUTTON;
@property (readonly) NSString* ENABLE_PUSHY_ENTERPRISE_REGISTRATION;
@property (readonly) NSString* ENABLE_NON_PEAK_HEAT_MAP;
@property (readonly) NSString* ENABLE_CAPTAIN_STATUS_API;
@property (readonly) NSString* ENABLE_PUSH_REGISTRATION_API;
@property (readonly) NSString* ENABLE_LOST_OFFER_API;
@property (readonly) NSString* DISABLE_BOOKING_ACTIVITY_TIME_ADJUSTMENT;
@property (readonly) NSString* ENABLE_TRACK_MY_REFERRAL;
@property (readonly) NSString* DISABLE_CUSTOMER_STARS_RATING;
@property (readonly) NSString* DISABLE_ADMA_CCT;
@property (readonly) NSString* ENABLE_FAQ;
@property (readonly) NSString* ENABLE_NEW_CAPTAIN_RATING_API;
@property (readonly) NSString* ENABLE_DISPUTE_INBOX_DIALOG;
@property (readonly) NSString* DISPUTE_RESPONSE_ETA_IN_HOURS;
@property (readonly) NSString* ENABLE_GCM_PUSH_REDIRECT;
@property (readonly) NSString* ENABLE_NEW_CASH_COLLECTION_UI;
@property (readonly) NSString* ENABLE_UNDERPAYMENT_DETAILS;
@property (readonly) NSString* DISABLE_CUSTOMER_TRIP_RATING_TRACKING;
@property (readonly) NSString* ENABLE_NO_INTERNET_CONNECTION_WARNING_ON_WEB_VIEW;
@property (readonly) NSString* ENABLE_ADD_DROPOFF_LOCATION;
@property (readonly) NSString* ENABLE_NEW_DISPUTE_COMMENT_API;
@property (readonly) NSString* ENABLE_ISSUE_INBOX_NEW_ORDERING;
@property (readonly) NSString* ENABLE_DISPUTE_STATUS_NEED_REPLY_NEW_DISPLAY;
@property (readonly) NSString* ENABLE_OPTION_TO_REOPEN_DISPUTE;
@property (readonly) NSString* BRAZE_SDK_ENABLED;
@property (readonly) NSString* ENABLE_ENCOURAGE_OPT_IN_ALERT;
@property (readonly) NSString* ENCOURAGE_OPT_IN_IDLE_TIME_MINUTES;
@property (readonly) NSString* ENABLE_BLOCK_BOOKING_OFFER_ACCEPTING_WHEN_OFFLINE;
@property (readonly) NSString* ENABLE_HELPLINES;
@property (readonly) NSString* HELPLINES_PHONE_NUMBER;
@property (readonly) NSString* ENABLE_DISPATCH_IN_RIDE;
@property (readonly) NSString* ENABLE_PUSH_TOKEN_REFRESH_IN_LOST_OFFER_SERVICE;
@property (readonly) NSString* ENABLE_THOR_UI_FLOW;
@property (readonly) NSString* ENABLE_DISPATCH_OPT_OUT;
@property (readonly) NSString* LAST_CAPTAIN_RATINGS_COUNT;
@property (readonly) NSString* CAPTAIN_BLOCKING_THRESHOLD;
@property (readonly) NSString* CAPTAIN_MIN_DISPLAY_RATINGS;
@property (readonly) NSString* ENABLE_RATING_REASON_COMMENT;
@property (readonly) NSString* ENABLE_SELECT_DISPUTE_OPTION;
@property (readonly) NSString* ENABLE_SENTIANCE_SDK;
@property (readonly) NSString* ENABLE_SMS_INBOX;
@property (readonly) NSString* POOLING_DISPLAY_NAME;
@property (readonly) NSString* ENABLE_DISPLAY_POOLING_NUMBER_OF_PASSENGERS_ON_CONFIRMATION;
@property (readonly) NSString* ENABLE_DISPLAY_POOLING_GENDER_ON_CONFIRMATION;
@property (readonly) NSString* ENABLE_CAR_UID_API;
@end;

@protocol CMECityConfigurationModel
@required
@property int32_t outsideBackOutDangerPeriodNormal;
@property (readonly) int32_t backOutDangerPeriodNormal;
@property (readonly) int32_t backOutDangerPeriodCorporate;
@property (readonly) int32_t backOutDangerPeriodVip;
@property (readonly) int32_t insideBackOutDangerPeriodNormal;
@property (readonly) int32_t insideBackOutDangerPeriodCorporate;
@property (readonly) int32_t insideBackOutDangerPeriodVip;
@property (readonly) int32_t outsideBackOutDangerPeriodCorporate;
@property (readonly) int32_t outsideBackOutDangerPeriodVip;
@property (readonly) BOOL isDispatchInRideEnabled;
@property (readonly) int32_t nowBookingPickupTimeValidityThresholdInMins;
@end;

@protocol CMELocationModel
@required
@end;

__attribute__((objc_subclassing_restricted))
@interface CMENavigationStop : KotlinBase
-(instancetype)initWithBookingId:(int64_t)bookingId stopType:(CMEStopType*)stopType NS_SWIFT_NAME(init(bookingId:stopType:)) NS_DESIGNATED_INITIALIZER;

-(int64_t)component1 NS_SWIFT_NAME(component1());
-(CMEStopType*)component2 NS_SWIFT_NAME(component2());
-(CMENavigationStop*)doCopyBookingId:(int64_t)bookingId stopType:(CMEStopType*)stopType NS_SWIFT_NAME(doCopy(bookingId:stopType:));
@property (readonly) int64_t bookingId;
@property (readonly) CMEStopType* stopType;
@end;

__attribute__((objc_subclassing_restricted))
@interface CMERoute : KotlinBase
-(instancetype)initWithBookings:(NSSet<CMEBooking*>*)bookings navigationStops:(NSArray<CMENavigationStop*>*)navigationStops isPooling:(BOOL)isPooling NS_SWIFT_NAME(init(bookings:navigationStops:isPooling:)) NS_DESIGNATED_INITIALIZER;

-(BOOL)containsBookingIdBookingId:(int64_t)bookingId NS_SWIFT_NAME(containsBookingId(bookingId:));
-(CMEBooking*)firstBooking NS_SWIFT_NAME(firstBooking());
-(CMEBooking* _Nullable)getBookingByIdBookingId:(int64_t)bookingId NS_SWIFT_NAME(getBookingById(bookingId:));
-(NSSet<CMEBooking*>*)component1 NS_SWIFT_NAME(component1());
-(NSArray<CMENavigationStop*>*)component2 NS_SWIFT_NAME(component2());
-(BOOL)component3 NS_SWIFT_NAME(component3());
-(CMERoute*)doCopyBookings:(NSSet<CMEBooking*>*)bookings navigationStops:(NSArray<CMENavigationStop*>*)navigationStops isPooling:(BOOL)isPooling NS_SWIFT_NAME(doCopy(bookings:navigationStops:isPooling:));
@property (readonly) NSSet<CMEBooking*>* bookings;
@property (readonly) NSArray<CMENavigationStop*>* navigationStops;
@property (readonly) BOOL isPooling;
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEStateError : CMEStdlibEnum
+(instancetype)alloc __attribute__((unavailable));
+(instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));

@property (class, readonly) CMEStateError* tripEndFailed;

-(instancetype)initWithName:(NSString*)name ordinal:(int32_t)ordinal NS_SWIFT_NAME(init(name:ordinal:)) NS_DESIGNATED_INITIALIZER __attribute__((unavailable));

-(int32_t)compareToOther:(CMEStateError*)other NS_SWIFT_NAME(compareTo(other:));
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEStopType : CMEStdlibEnum
+(instancetype)alloc __attribute__((unavailable));
+(instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));

@property (class, readonly) CMEStopType* pickup;
@property (class, readonly) CMEStopType* dropoff;

-(instancetype)initWithName:(NSString*)name ordinal:(int32_t)ordinal NS_SWIFT_NAME(init(name:ordinal:)) NS_DESIGNATED_INITIALIZER __attribute__((unavailable));

-(int32_t)compareToOther:(CMEStopType*)other NS_SWIFT_NAME(compareTo(other:));
@property (readonly) int32_t code;
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEStopTypeCompanion : KotlinBase
+(instancetype)alloc __attribute__((unavailable));
+(instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));

+(instancetype)companion NS_SWIFT_NAME(init());

-(CMEStopType* _Nullable)fromCodeCode:(int32_t)code NS_SWIFT_NAME(fromCode(code:));
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEBookingCancelledAction : CMEAction
-(instancetype)initWithCancelledBooking:(CMEBooking*)cancelledBooking navigationStops:(NSArray<CMENavigationStop*>* _Nullable)navigationStops NS_SWIFT_NAME(init(cancelledBooking:navigationStops:)) NS_DESIGNATED_INITIALIZER;

-(instancetype)init NS_SWIFT_NAME(init()) NS_DESIGNATED_INITIALIZER __attribute__((unavailable));

-(CMEBooking*)component1 NS_SWIFT_NAME(component1());
-(NSArray<CMENavigationStop*>* _Nullable)component2 NS_SWIFT_NAME(component2());
-(CMEBookingCancelledAction*)doCopyCancelledBooking:(CMEBooking*)cancelledBooking navigationStops:(NSArray<CMENavigationStop*>* _Nullable)navigationStops NS_SWIFT_NAME(doCopy(cancelledBooking:navigationStops:));
@property (readonly) CMEBooking* cancelledBooking;
@property (readonly) NSArray<CMENavigationStop*>* _Nullable navigationStops;
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEStdlibPair : KotlinBase
-(instancetype)initWithFirst:(id _Nullable)first second:(id _Nullable)second NS_SWIFT_NAME(init(first:second:)) NS_DESIGNATED_INITIALIZER;

-(id _Nullable)component1 NS_SWIFT_NAME(component1());
-(id _Nullable)component2 NS_SWIFT_NAME(component2());
-(CMEStdlibPair*)doCopyFirst:(id _Nullable)first second:(id _Nullable)second NS_SWIFT_NAME(doCopy(first:second:));
@property (readonly) id _Nullable first;
@property (readonly) id _Nullable second;
@end;

@interface CMEStdlibThrowable : KotlinBase
-(instancetype)initWithMessage:(NSString* _Nullable)message NS_SWIFT_NAME(init(message:)) NS_DESIGNATED_INITIALIZER;

-(instancetype)initWithCause:(CMEStdlibThrowable* _Nullable)cause NS_SWIFT_NAME(init(cause:)) NS_DESIGNATED_INITIALIZER;

-(instancetype)init NS_SWIFT_NAME(init()) NS_DESIGNATED_INITIALIZER;

-(instancetype)initWithMessage:(NSString* _Nullable)message cause:(CMEStdlibThrowable* _Nullable)cause NS_SWIFT_NAME(init(message:cause:)) NS_DESIGNATED_INITIALIZER;

-(void)printStackTrace NS_SWIFT_NAME(printStackTrace());
@property (readonly) CMEStdlibThrowable* _Nullable cause;
@property (readonly) NSString* _Nullable message;
@end;

@interface CMEStdlibException : CMEStdlibThrowable
-(instancetype)init NS_SWIFT_NAME(init()) NS_DESIGNATED_INITIALIZER;

-(instancetype)initWithMessage:(NSString*)message NS_SWIFT_NAME(init(message:)) NS_DESIGNATED_INITIALIZER;

-(instancetype)initWithMessage:(NSString*)message cause:(CMEStdlibThrowable*)cause NS_SWIFT_NAME(init(message:cause:)) NS_DESIGNATED_INITIALIZER;

-(instancetype)initWithCause:(CMEStdlibThrowable*)cause NS_SWIFT_NAME(init(cause:)) NS_DESIGNATED_INITIALIZER;

@end;

@protocol CMEStdlibKDeclarationContainer
@required
@end;

@protocol CMEStdlibKAnnotatedElement
@required
@end;

@protocol CMEStdlibKClassifier
@required
@end;

@protocol CMEStdlibKClass <CMEStdlibKDeclarationContainer, CMEStdlibKAnnotatedElement, CMEStdlibKClassifier>
@required
-(BOOL)isInstanceValue:(id _Nullable)value NS_SWIFT_NAME(isInstance(value:));
@property (readonly) NSString* _Nullable qualifiedName;
@property (readonly) NSString* _Nullable simpleName;
@end;

__attribute__((objc_subclassing_restricted))
@interface CMEStdlibUnit : KotlinBase
+(instancetype)alloc __attribute__((unavailable));
+(instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));

+(instancetype)unit NS_SWIFT_NAME(init());

@end;

NS_ASSUME_NONNULL_END
