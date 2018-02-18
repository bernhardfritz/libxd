#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#define KEY_ESCAPE GLFW_KEY_ESCAPE               // 256
#define KEY_ENTER GLFW_KEY_ENTER                 // 257
#define KEY_TAB GLFW_KEY_TAB                     // 258
#define KEY_BACKSPACE GLFW_KEY_BACKSPACE         // 259
#define KEY_INSERT GLFW_KEY_INSERT               // 260
#define KEY_DELETE GLFW_KEY_DELETE               // 261
#define KEY_RIGHT GLFW_KEY_RIGHT                 // 262
#define KEY_LEFT GLFW_KEY_LEFT                   // 263
#define KEY_DOWN GLFW_KEY_DOWN                   // 264
#define KEY_UP GLFW_KEY_UP                       // 265
#define KEY_PAGE_UP GLFW_KEY_PAGE_UP             // 266
#define KEY_PAGE_DOWN GLFW_KEY_PAGE_DOWN         // 267
#define KEY_HOME GLFW_KEY_HOME                   // 268
#define KEY_END GLFW_KEY_END                     // 269
#define KEY_CAPS_LOCK GLFW_KEY_CAPS_LOCK         // 280
#define KEY_SCROLL_LOCK GLFW_KEY_SCROLL_LOCK     // 281
#define KEY_NUM_LOCK GLFW_KEY_NUM_LOCK           // 282
#define KEY_PRINT_SCREEN GLFW_KEY_PRINT_SCREEN   // 283
#define KEY_PAUSE GLFW_KEY_PAUSE                 // 284
#define KEY_F1 GLFW_KEY_F1                       // 290
#define KEY_F2 GLFW_KEY_F2                       // 291
#define KEY_F3 GLFW_KEY_F3                       // 292
#define KEY_F4 GLFW_KEY_F4                       // 293
#define KEY_F5 GLFW_KEY_F5                       // 294
#define KEY_F6 GLFW_KEY_F6                       // 295
#define KEY_F7 GLFW_KEY_F7                       // 296
#define KEY_F8 GLFW_KEY_F8                       // 297
#define KEY_F9 GLFW_KEY_F9                       // 298
#define KEY_F10 GLFW_KEY_F10                     // 299
#define KEY_F11 GLFW_KEY_F11                     // 300
#define KEY_F12 GLFW_KEY_F12                     // 301
#define KEY_F13 GLFW_KEY_F13                     // 302
#define KEY_F14 GLFW_KEY_F14                     // 303
#define KEY_F15 GLFW_KEY_F15                     // 304
#define KEY_F16	GLFW_KEY_F16                     // 305
#define KEY_F17	GLFW_KEY_F17                     // 306
#define KEY_F18	GLFW_KEY_F18                     // 307
#define KEY_F19 GLFW_KEY_F19                     // 308
#define KEY_F20 GLFW_KEY_F20                     // 309
#define KEY_F21 GLFW_KEY_F21                     // 310
#define KEY_F22 GLFW_KEY_F22                     // 311
#define KEY_F23 GLFW_KEY_F23                     // 312
#define KEY_F24 GLFW_KEY_F24                     // 313
#define KEY_F25 GLFW_KEY_F25                     // 314
#define KEY_KP_0 GLFW_KEY_KP_0                   // 320
#define KEY_KP_1 GLFW_KEY_KP_1                   // 321
#define KEY_KP_2 GLFW_KEY_KP_2                   // 322
#define KEY_KP_3 GLFW_KEY_KP_3                   // 323
#define KEY_KP_4 GLFW_KEY_KP_4                   // 324
#define KEY_KP_5 GLFW_KEY_KP_5                   // 325
#define KEY_KP_6 GLFW_KEY_KP_6                   // 326
#define KEY_KP_7 GLFW_KEY_KP_7                   // 327
#define KEY_KP_8 GLFW_KEY_KP_8                   // 328
#define KEY_KP_9 GLFW_KEY_KP_9                   // 329
#define KEY_KP_DECIMAL GLFW_KEY_KP_DECIMAL       // 330
#define KEY_KP_DIVIDE GLFW_KEY_KP_DIVIDE         // 331
#define KEY_KP_MULTIPLY GLFW_KEY_KP_MULTIPLY     // 332
#define KEY_KP_SUBTRACT GLFW_KEY_KP_SUBTRACT     // 333
#define KEY_KP_ADD GLFW_KEY_KP_ADD               // 334
#define KEY_KP_ENTER GLFW_KEY_KP_ENTER           // 335
#define KEY_KP_EQUAL GLFW_KEY_KP_EQUAL           // 336
#define KEY_LEFT_SHIFT GLFW_KEY_LEFT_SHIFT       // 340
#define KEY_LEFT_CONTROL GLFW_KEY_LEFT_CONTROL   // 341
#define KEY_LEFT_ALT GLFW_KEY_LEFT_ALT           // 342
#define KEY_LEFT_SUPER GLFW_KEY_LEFT_SUPER       // 343
#define KEY_RIGHT_SHIFT GLFW_KEY_RIGHT_SHIFT     // 344
#define KEY_RIGHT_CONTROL GLFW_KEY_RIGHT_CONTROL // 345
#define KEY_RIGHT_ALT GLFW_KEY_RIGHT_ALT         // 346
#define KEY_RIGHT_SUPER GLFW_KEY_RIGHT_SUPER     // 347
#define KEY_MENU GLFW_KEY_MENU                   // 348

namespace xd {

void keyPressed(void (*onKeyPressed)(int));   // onKeyPressed(key)
void keyReleased(void (*onKeyReleased)(int)); // onKeyReleased(key)

} // namespace xd

#endif /* KEYBOARD_HPP */
