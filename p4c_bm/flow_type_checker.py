import p4_hlir.hlir.p4 as p4
from tenjin.util import *
import sys
import os
import json
import argparse
import cPickle as pickle
import re

ACTION_TYPE = "action"
PRIORITY_TYPE = "priority" 
OUTPUT_VAL = "output"
DEPARSE_VAL = "deparse"

def exit_with_error(error_msg):
  """ Exit with error code after printing the error """
  sys.stderr.write("flow_type_checker: Error: %s\n" % error_msg)
  sys.exit(1)


def get_parser():
  """ Parser definition for the flow type checker. """
  parser = argparse.ArgumentParser(description='PIECES flow type checker arguments')
  parser.add_argument('parse_dict_file',
    metavar='parse_dict_file',
    type=str,
    help='Location of the parser definition dictionary file'
      ' with p4 to ovs parser specification.')

  parser.add_argument('--add-flow',
    action='store_true',
    default=False,
    help='Toggle add flow')

  parser.add_argument('--check-flow',
    action='store_true',
    default=False,
    help='Toggle to only check flow')

  parser.add_argument('--br',
    metavar='bridge_name',
    type=str,
    default=None,
    help='Bridge name. ex: --br br0')

  parser.add_argument('--match',
    metavar='match_vals',
    type=str,
    default=None,
    help='Match values for the flow.\n'
      'ex: --match "table=0,priority=32768"')

  parser.add_argument('--action',
    metavar='action_vals',
    type=str,
    default=None,
    help='Action values for the flow.\n'
      'ex: --action "actions=resubmit(,1)"')

  parser.add_argument('--ofctl-path',
    metavar='ofctl_path',
    type=str,
    default=None,
    help='Path of the ovs ofctl to invoke')
  return parser


def check_flow_type(match_vals, action_vals, parser_def_dict):
  """ Checks the flow type to see if it is correct. """
  if not match_vals:
    exit_with_error("No match values given")
  if not action_vals:
    exit_with_error("No action values given")

  # Checking the match variables
  match_list = match_vals.split(",")
  for match_elem in match_list:
    try:
      match_name, match_val = match_elem.split("=")
    except Exception:
      exit_with_error("Invalid match format.")
    print match_name, match_val

  # Checking the actions
  action_name, actions = action_vals.split("=")
  if action_name != ACTION_TYPE:
    exit_with_error("Invalid action type name")
  r = re.compile(r'(?:[^,(]|\([^)]*\))+')
  action_list = r.findall(actions) 
  for action in action_list:
    action_elems = action.split(":")
    # This is the case when there is only one action
    if len(action_elems) == 1:
      pass
    # This is the case when there is an argument to a function 
    elif len(action_elems) == 2:
      action_name, action_arg = action_elems
    else:
      exit_with_error("Invalid number of arguments for an action")

  return True


def main():
  parser = get_parser()
  input_args = sys.argv[1:]
  args, unparsed_args = parser.parse_known_args()
  parse_dict = None
  try:
    parse_dict = pickle.load(open(args.parse_dict_file, "rb"))
  except Exception:
    exit_with_error("Failed to load the parse dictionary file")

  if not args.add_flow and not args.check_flow:
    exit_with_error("You must either add or check flow")

  flow_type_arg = None
  add_flow = args.add_flow
  match_vals = args.match
  action_vals = args.action
  bridge_name = args.br
  if not bridge_name:
    exit_with_error("No bridge name given")

  check_flow_type(match_vals, action_vals, parse_dict)

if __name__ == "__main__":
    main()
