/*
 * Copyright (C) 2015-2018 Swift Navigation Inc.
 * Contact: Swift Navigation <dev@swiftnav.com>
 *
 * This source is subject to the license found in the file 'LICENSE' which must
 * be be distributed together with this source. All other rights reserved.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 */

// This file was auto-generated from spec/tests/yaml/swiftnav/sbp/navigation/test_MsgBaselineNED.yaml by generate.py. Do not modify by hand!

#include <check.h>
#include <stdio.h> // for debugging
#include <stdlib.h> // for malloc
#include <sbp.h>
#include <navigation.h>

static u32 n_callbacks_logged;
static u16 last_sender_id;
static u8 last_len;
static u8 last_msg[256];
static void* last_context;

static u32 dummy_wr = 0;
static u32 dummy_rd = 0;
static u8 dummy_buff[1024];
static void* last_io_context;

static int DUMMY_MEMORY_FOR_CALLBACKS = 0xdeadbeef;
static int DUMMY_MEMORY_FOR_IO = 0xdead0000;

static void dummy_reset()
{
  dummy_rd = dummy_wr = 0;
  memset(dummy_buff, 0, sizeof(dummy_buff));
}

static u32 dummy_write(u8 *buff, u32 n, void* context)
{
 last_io_context = context;
 u32 real_n = n;//(dummy_n > n) ? n : dummy_n;
 memcpy(dummy_buff + dummy_wr, buff, real_n);
 dummy_wr += real_n;
 return real_n;
}

static u32 dummy_read(u8 *buff, u32 n, void* context)
{
 last_io_context = context;
 u32 real_n = n;//(dummy_n > n) ? n : dummy_n;
 memcpy(buff, dummy_buff + dummy_rd, real_n);
 dummy_rd += real_n;
 return real_n;
}

static void logging_reset()
{
  n_callbacks_logged = 0;
  last_context = 0;
  memset(last_msg, 0, sizeof(last_msg));
}

static void logging_callback(u16 sender_id, u8 len, u8 msg[], void* context)
{
  n_callbacks_logged++;
  last_sender_id = sender_id;
  last_len = len;
  last_context = context;
  memcpy(last_msg, msg, len);

  /*printy_callback(sender_id, len, msg);*/
}

START_TEST( test_auto_check_sbp_navigation_6 )
{
  static sbp_msg_callbacks_node_t n;
  //static sbp_msg_callbacks_node_t n2;

  // State of the SBP message parser.
  // Must be statically allocated.
  sbp_state_t sbp_state;

  //
  // Run tests:
  //
  // Test successful parsing of a message
  {
    // SBP parser state must be initialized before sbp_process is called.
    // We re-initialize before every test so that callbacks for the same message types can be
    //  allocated multiple times across different tests.
    sbp_state_init(&sbp_state);

    sbp_state_set_io_context(&sbp_state, &DUMMY_MEMORY_FOR_IO);

    logging_reset();

    sbp_register_callback(&sbp_state, 0x20c, &logging_callback, &DUMMY_MEMORY_FOR_CALLBACKS, &n);

    u8 test_data[] = {85,12,2,211,136,22,40,244,122,19,201,115,12,0,179,88,230,255,153,125,0,0,0,0,0,0,14,0,226,70, };

    dummy_reset();
    sbp_send_message(&sbp_state, 0x20c, 35027, sizeof(test_data), test_data, &dummy_write);

    while (dummy_rd < dummy_wr) {
      fail_unless(sbp_process(&sbp_state, &dummy_read) >= SBP_OK,
          "sbp_process threw an error!");
    }

    fail_unless(n_callbacks_logged == 1,
        "one callback should have been logged");
    fail_unless(last_sender_id == 35027,
        "sender_id decoded incorrectly");
    fail_unless(last_len == sizeof(test_data),
        "len decoded incorrectly");
    fail_unless(memcmp(last_msg, test_data, sizeof(test_data))
          == 0,
        "test data decoded incorrectly");
    fail_unless(last_context == &DUMMY_MEMORY_FOR_CALLBACKS,
        "context pointer incorrectly passed");

    // Cast to expected message type - the +6 byte offset is where the payload starts
    msg_baseline_ned_t* msg = ( msg_baseline_ned_t *)((void *)last_msg + 6);
    // Run tests against fields
    fail_unless(msg != 0, "stub to prevent warnings if msg isn't used");
    fail_unless(msg->d == 32153, "incorrect value for d, expected 32153, is %d", msg->d);
    fail_unless(msg->e == -1681229, "incorrect value for e, expected -1681229, is %d", msg->e);
    fail_unless(msg->flags == 0, "incorrect value for flags, expected 0, is %d", msg->flags);
    fail_unless(msg->h_accuracy == 0, "incorrect value for h_accuracy, expected 0, is %d", msg->h_accuracy);
    fail_unless(msg->n == 816073, "incorrect value for n, expected 816073, is %d", msg->n);
    fail_unless(msg->n_sats == 14, "incorrect value for n_sats, expected 14, is %d", msg->n_sats);
    fail_unless(msg->tow == 326825000, "incorrect value for tow, expected 326825000, is %d", msg->tow);
    fail_unless(msg->v_accuracy == 0, "incorrect value for v_accuracy, expected 0, is %d", msg->v_accuracy);
  }
  // Test successful parsing of a message
  {
    // SBP parser state must be initialized before sbp_process is called.
    // We re-initialize before every test so that callbacks for the same message types can be
    //  allocated multiple times across different tests.
    sbp_state_init(&sbp_state);

    sbp_state_set_io_context(&sbp_state, &DUMMY_MEMORY_FOR_IO);

    logging_reset();

    sbp_register_callback(&sbp_state, 0x20c, &logging_callback, &DUMMY_MEMORY_FOR_CALLBACKS, &n);

    u8 test_data[] = {85,12,2,211,136,22,16,248,122,19,98,115,12,0,194,88,230,255,110,127,0,0,0,0,0,0,15,0,69,93, };

    dummy_reset();
    sbp_send_message(&sbp_state, 0x20c, 35027, sizeof(test_data), test_data, &dummy_write);

    while (dummy_rd < dummy_wr) {
      fail_unless(sbp_process(&sbp_state, &dummy_read) >= SBP_OK,
          "sbp_process threw an error!");
    }

    fail_unless(n_callbacks_logged == 1,
        "one callback should have been logged");
    fail_unless(last_sender_id == 35027,
        "sender_id decoded incorrectly");
    fail_unless(last_len == sizeof(test_data),
        "len decoded incorrectly");
    fail_unless(memcmp(last_msg, test_data, sizeof(test_data))
          == 0,
        "test data decoded incorrectly");
    fail_unless(last_context == &DUMMY_MEMORY_FOR_CALLBACKS,
        "context pointer incorrectly passed");

    // Cast to expected message type - the +6 byte offset is where the payload starts
    msg_baseline_ned_t* msg = ( msg_baseline_ned_t *)((void *)last_msg + 6);
    // Run tests against fields
    fail_unless(msg != 0, "stub to prevent warnings if msg isn't used");
    fail_unless(msg->d == 32622, "incorrect value for d, expected 32622, is %d", msg->d);
    fail_unless(msg->e == -1681214, "incorrect value for e, expected -1681214, is %d", msg->e);
    fail_unless(msg->flags == 0, "incorrect value for flags, expected 0, is %d", msg->flags);
    fail_unless(msg->h_accuracy == 0, "incorrect value for h_accuracy, expected 0, is %d", msg->h_accuracy);
    fail_unless(msg->n == 815970, "incorrect value for n, expected 815970, is %d", msg->n);
    fail_unless(msg->n_sats == 15, "incorrect value for n_sats, expected 15, is %d", msg->n_sats);
    fail_unless(msg->tow == 326826000, "incorrect value for tow, expected 326826000, is %d", msg->tow);
    fail_unless(msg->v_accuracy == 0, "incorrect value for v_accuracy, expected 0, is %d", msg->v_accuracy);
  }
  // Test successful parsing of a message
  {
    // SBP parser state must be initialized before sbp_process is called.
    // We re-initialize before every test so that callbacks for the same message types can be
    //  allocated multiple times across different tests.
    sbp_state_init(&sbp_state);

    sbp_state_set_io_context(&sbp_state, &DUMMY_MEMORY_FOR_IO);

    logging_reset();

    sbp_register_callback(&sbp_state, 0x20c, &logging_callback, &DUMMY_MEMORY_FOR_CALLBACKS, &n);

    u8 test_data[] = {85,12,2,211,136,22,248,251,122,19,143,114,12,0,173,88,230,255,238,127,0,0,0,0,0,0,15,0,210,169, };

    dummy_reset();
    sbp_send_message(&sbp_state, 0x20c, 35027, sizeof(test_data), test_data, &dummy_write);

    while (dummy_rd < dummy_wr) {
      fail_unless(sbp_process(&sbp_state, &dummy_read) >= SBP_OK,
          "sbp_process threw an error!");
    }

    fail_unless(n_callbacks_logged == 1,
        "one callback should have been logged");
    fail_unless(last_sender_id == 35027,
        "sender_id decoded incorrectly");
    fail_unless(last_len == sizeof(test_data),
        "len decoded incorrectly");
    fail_unless(memcmp(last_msg, test_data, sizeof(test_data))
          == 0,
        "test data decoded incorrectly");
    fail_unless(last_context == &DUMMY_MEMORY_FOR_CALLBACKS,
        "context pointer incorrectly passed");

    // Cast to expected message type - the +6 byte offset is where the payload starts
    msg_baseline_ned_t* msg = ( msg_baseline_ned_t *)((void *)last_msg + 6);
    // Run tests against fields
    fail_unless(msg != 0, "stub to prevent warnings if msg isn't used");
    fail_unless(msg->d == 32750, "incorrect value for d, expected 32750, is %d", msg->d);
    fail_unless(msg->e == -1681235, "incorrect value for e, expected -1681235, is %d", msg->e);
    fail_unless(msg->flags == 0, "incorrect value for flags, expected 0, is %d", msg->flags);
    fail_unless(msg->h_accuracy == 0, "incorrect value for h_accuracy, expected 0, is %d", msg->h_accuracy);
    fail_unless(msg->n == 815759, "incorrect value for n, expected 815759, is %d", msg->n);
    fail_unless(msg->n_sats == 15, "incorrect value for n_sats, expected 15, is %d", msg->n_sats);
    fail_unless(msg->tow == 326827000, "incorrect value for tow, expected 326827000, is %d", msg->tow);
    fail_unless(msg->v_accuracy == 0, "incorrect value for v_accuracy, expected 0, is %d", msg->v_accuracy);
  }
  // Test successful parsing of a message
  {
    // SBP parser state must be initialized before sbp_process is called.
    // We re-initialize before every test so that callbacks for the same message types can be
    //  allocated multiple times across different tests.
    sbp_state_init(&sbp_state);

    sbp_state_set_io_context(&sbp_state, &DUMMY_MEMORY_FOR_IO);

    logging_reset();

    sbp_register_callback(&sbp_state, 0x20c, &logging_callback, &DUMMY_MEMORY_FOR_CALLBACKS, &n);

    u8 test_data[] = {85,12,2,211,136,22,224,255,122,19,86,112,12,0,51,88,230,255,47,127,0,0,0,0,0,0,15,0,135,107, };

    dummy_reset();
    sbp_send_message(&sbp_state, 0x20c, 35027, sizeof(test_data), test_data, &dummy_write);

    while (dummy_rd < dummy_wr) {
      fail_unless(sbp_process(&sbp_state, &dummy_read) >= SBP_OK,
          "sbp_process threw an error!");
    }

    fail_unless(n_callbacks_logged == 1,
        "one callback should have been logged");
    fail_unless(last_sender_id == 35027,
        "sender_id decoded incorrectly");
    fail_unless(last_len == sizeof(test_data),
        "len decoded incorrectly");
    fail_unless(memcmp(last_msg, test_data, sizeof(test_data))
          == 0,
        "test data decoded incorrectly");
    fail_unless(last_context == &DUMMY_MEMORY_FOR_CALLBACKS,
        "context pointer incorrectly passed");

    // Cast to expected message type - the +6 byte offset is where the payload starts
    msg_baseline_ned_t* msg = ( msg_baseline_ned_t *)((void *)last_msg + 6);
    // Run tests against fields
    fail_unless(msg != 0, "stub to prevent warnings if msg isn't used");
    fail_unless(msg->d == 32559, "incorrect value for d, expected 32559, is %d", msg->d);
    fail_unless(msg->e == -1681357, "incorrect value for e, expected -1681357, is %d", msg->e);
    fail_unless(msg->flags == 0, "incorrect value for flags, expected 0, is %d", msg->flags);
    fail_unless(msg->h_accuracy == 0, "incorrect value for h_accuracy, expected 0, is %d", msg->h_accuracy);
    fail_unless(msg->n == 815190, "incorrect value for n, expected 815190, is %d", msg->n);
    fail_unless(msg->n_sats == 15, "incorrect value for n_sats, expected 15, is %d", msg->n_sats);
    fail_unless(msg->tow == 326828000, "incorrect value for tow, expected 326828000, is %d", msg->tow);
    fail_unless(msg->v_accuracy == 0, "incorrect value for v_accuracy, expected 0, is %d", msg->v_accuracy);
  }
  // Test successful parsing of a message
  {
    // SBP parser state must be initialized before sbp_process is called.
    // We re-initialize before every test so that callbacks for the same message types can be
    //  allocated multiple times across different tests.
    sbp_state_init(&sbp_state);

    sbp_state_set_io_context(&sbp_state, &DUMMY_MEMORY_FOR_IO);

    logging_reset();

    sbp_register_callback(&sbp_state, 0x20c, &logging_callback, &DUMMY_MEMORY_FOR_CALLBACKS, &n);

    u8 test_data[] = {85,12,2,211,136,22,200,3,123,19,214,110,12,0,220,87,230,255,165,126,0,0,0,0,0,0,15,0,190,80, };

    dummy_reset();
    sbp_send_message(&sbp_state, 0x20c, 35027, sizeof(test_data), test_data, &dummy_write);

    while (dummy_rd < dummy_wr) {
      fail_unless(sbp_process(&sbp_state, &dummy_read) >= SBP_OK,
          "sbp_process threw an error!");
    }

    fail_unless(n_callbacks_logged == 1,
        "one callback should have been logged");
    fail_unless(last_sender_id == 35027,
        "sender_id decoded incorrectly");
    fail_unless(last_len == sizeof(test_data),
        "len decoded incorrectly");
    fail_unless(memcmp(last_msg, test_data, sizeof(test_data))
          == 0,
        "test data decoded incorrectly");
    fail_unless(last_context == &DUMMY_MEMORY_FOR_CALLBACKS,
        "context pointer incorrectly passed");

    // Cast to expected message type - the +6 byte offset is where the payload starts
    msg_baseline_ned_t* msg = ( msg_baseline_ned_t *)((void *)last_msg + 6);
    // Run tests against fields
    fail_unless(msg != 0, "stub to prevent warnings if msg isn't used");
    fail_unless(msg->d == 32421, "incorrect value for d, expected 32421, is %d", msg->d);
    fail_unless(msg->e == -1681444, "incorrect value for e, expected -1681444, is %d", msg->e);
    fail_unless(msg->flags == 0, "incorrect value for flags, expected 0, is %d", msg->flags);
    fail_unless(msg->h_accuracy == 0, "incorrect value for h_accuracy, expected 0, is %d", msg->h_accuracy);
    fail_unless(msg->n == 814806, "incorrect value for n, expected 814806, is %d", msg->n);
    fail_unless(msg->n_sats == 15, "incorrect value for n_sats, expected 15, is %d", msg->n_sats);
    fail_unless(msg->tow == 326829000, "incorrect value for tow, expected 326829000, is %d", msg->tow);
    fail_unless(msg->v_accuracy == 0, "incorrect value for v_accuracy, expected 0, is %d", msg->v_accuracy);
  }
}
END_TEST

Suite* auto_check_sbp_navigation_6_suite(void)
{
  Suite *s = suite_create("SBP generated test suite: auto_check_sbp_navigation_6");
  TCase *tc_acq = tcase_create("Automated_Suite_auto_check_sbp_navigation_6");
  tcase_add_test(tc_acq, test_auto_check_sbp_navigation_6);
  suite_add_tcase(s, tc_acq);
  return s;
}