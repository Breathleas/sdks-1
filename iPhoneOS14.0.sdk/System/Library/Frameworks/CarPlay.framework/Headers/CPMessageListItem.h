//
//  CPMessageListItem.h
//  CarPlay
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <CarPlay/CPBaseListItem.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Maximum size of an image or accessory image in a @c CPMessageListItem.
 */
extern CGSize const CPMaximumMessageItemImageSize;

/**
 Types of glyphs that may appear in the leading region of a message cell.
 */
typedef NS_ENUM(NSUInteger, CPMessageLeadingItem) {
    CPMessageLeadingItemNone, // The list item will render without a leading glyph.
    CPMessageLeadingItemPin,  // The list item will render with a pin glyph on the leading side.
    CPMessageLeadingItemStar  // The list item will render with a star glyph on the leading side.
};

/**
 Types of glyphs that may appear in the trailing region of a message cell.
 */
typedef NS_ENUM(NSUInteger, CPMessageTrailingItem) {
    CPMessageTrailingItemNone, // The list item will render without a trailing glyph.
    CPMessageTrailingItemMute  // The list item will render with a mute glyph on the trailing side.
};

/**
 @c CPMessageListItemLeadingConfiguration encapsulates the configuration options for
 the leading side of your message list cell.
 */
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPMessageListItemLeadingConfiguration : NSObject

@property (nonatomic, readonly, getter=isUnread) BOOL unread;
@property (nonatomic, readonly) CPMessageLeadingItem leadingItem;
@property (nonatomic, readonly, nullable) UIImage *leadingImage;

/**
 @param leadingItem An optional glyph displayed on the leading side of the cell.
 @param leadingImage An optional image displayed on the leading side of the cell.
 @param unread Whether this conversation is unread. If unread, the list item
 will render with an unread indicator and tapping this item will read the conversation. If read,
 no unread indicator will be displayed and tapping this item will compose a new message.
 
 @discussion To properly size your list images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
- (instancetype)initWithLeadingItem:(CPMessageLeadingItem)leadingItem
                       leadingImage:(nullable UIImage *)leadingImage
                             unread:(BOOL)unread NS_SWIFT_NAME(init(leadingItem:leadingImage:unread:));

@end

/**
 @c CPMessageListItemTrailingConfiguration encapsulates the configuration options for
 the trailing side of your message list cell.
 */
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPMessageListItemTrailingConfiguration : NSObject

@property (nonatomic, readonly) CPMessageTrailingItem trailingItem;
@property (nonatomic, readonly, nullable) UIImage *trailingImage;

/**
 @param trailingItem An optional glyph displayed on the trailing side of the cell.
 @param trailingImage An optional image displayed on the trailing side of the cell.
 
 @discussion To properly size your list images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
- (instancetype)initWithTrailingItem:(CPMessageTrailingItem)trailingItem
                       trailingImage:(nullable UIImage *)trailingImage;

@end

/**
 @c CPMessageListItem is a special variant of a list item for use in a @c CPListTemplate.
 Unlike @c CPListItem, your application will not receive a callback when the user
 selects a @c CPMessageListItem in your list template. Instead, Siri will be invoked
 using the parameters you specify in your message item and the user will continue a
 message compose, read, or reply flow through Siri.
 
 There are two modes of operation for @c CPMessageListItem:
 
   To represent an existing conversation with one or more recipients, use the @c CPMessageListItem
   initializer that accepts a conversation identifier. This identifier is not directly displayed
   to the user; rather, it should be a value meaningful to your app to identify the conversation.
 
   To represent a contact or person entity, use the @c CPMessageListItem initializer that
   accepts a full name and phone/email. When the user selects this item, Siri will perform
   a message compose flow.
 */
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPMessageListItem : CPBaseListItem

/**
 Initialize a @c CPMessageListItem for use in a @c CPListTemplate.

 @param conversationIdentifier A value meaningful to your app to identify this conversation.
 This identifier is not directly displayed to the user; rather, when the user selects this list item,
 SiriKit will pass this identifier back to your app for your own use.
 @param text This is the main text label displayed to the user as well as spoken by
 Siri when the user selects this list item.
 @param leadingConfiguration A set of configuration options for the leading side of the list item.
 @param trailingConfiguration A set of configuration options for the trailing side of the list item.
 @param detailText Any additional text displayed underneath the @c conversationName.
 @param trailingText Any additional text displayed along the trailing side of the cell.

 @note The maximum image size is CPMaximumMessageItemImageSize. If you supply a larger image,
 it will be scaled down to this size.
*/
- (instancetype)initWithConversationIdentifier:(NSString *)conversationIdentifier
                                          text:(NSString *)text
                          leadingConfiguration:(CPMessageListItemLeadingConfiguration *)leadingConfiguration
                         trailingConfiguration:(nullable CPMessageListItemTrailingConfiguration *)trailingConfiguration
                                    detailText:(nullable NSString *)detailText
                                  trailingText:(nullable NSString *)trailingText;

/**
 Initialize a @c CPMessageListItem for use in a @c CPListTemplate.

 @param fullName The full name of the contact entity represented by this list item. This text
 will be displayed as the main text label in the cell and will be spoken by Siri.
 @param phoneOrEmailAddress A phone or email address for this contact entity that can be used
 to compose a message.
 @param leadingConfiguration A set of configuration options for the leading side of the list item.
 @param trailingConfiguration A set of configuration options for the trailing side of the list item.
 @param detailText Any additional text displayed underneath the @c conversationName.
 @param trailingText Any additional text displayed along the trailing side of the cell.

 @note The maximum image size is CPMaximumMessageItemImageSize. If you supply a larger image,
 it will be scaled down to this size.
*/
- (instancetype)initWithFullName:(NSString *)fullName
             phoneOrEmailAddress:(NSString *)phoneOrEmailAddress
            leadingConfiguration:(CPMessageListItemLeadingConfiguration *)leadingConfiguration
           trailingConfiguration:(nullable CPMessageListItemTrailingConfiguration *)trailingConfiguration
                      detailText:(nullable NSString *)detailText
                    trailingText:(nullable NSString *)trailingText;

/**
 To update the @c CPMessageListItem, assign to any of these properties. If displayed in a
 list template, the list item will be automatically reloaded.
 */
@property (nonatomic, copy, nullable) NSString *conversationIdentifier;
@property (nonatomic, copy, nullable) NSString *phoneOrEmailAddress;
@property (nonatomic, strong) CPMessageListItemLeadingConfiguration *leadingConfiguration;
@property (nonatomic, strong, nullable) CPMessageListItemTrailingConfiguration *trailingConfiguration;
@property (nonatomic, copy, nullable) NSString *detailText;
@property (nonatomic, copy, nullable) NSString *trailingText;

/**
 Handlers are not invoked when the user selects this list item in a list template. Instead, Siri
 will be invoked using the parameters you specify in your message list item and the user will
 continue a message compose, read, or reply flow through Siri.
 */
@property (nonatomic, copy, nullable) CPListItemHandler listItemHandler API_UNAVAILABLE(ios);

@end

NS_ASSUME_NONNULL_END
