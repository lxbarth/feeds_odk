<?php

/**
 * Batch object containing the submitted data.
 */
class FeedsODKBatch extends FeedsImportBatch {
  protected $file_submission;

  /**
   * Constructor.
   */
  public function __construct($file_submission) {
    $this->file_submission = $file_submission;
    feeds_odk_log($this->file_submission);
  }

  /**
   * Return the raw XML of the submission.
   */
  public function getRaw() {
    $handle = fopen($_FILES['xml_submission_file']['tmp_name'], 'r');
    $contents = fread($handle, filesize($_FILES['xml_submission_file']['tmp_name']));
    fclose($handle);
    return $contents;
  }

  /**
   * Get the raw submitted data.
   */
  public function getRawSubmission() {
    return $this->file_submission;
  }
}

/**
 * Receives an ODK post.
 */
class FeedsODKFetcher extends FeedsFetcher {
  /**
   * Implement FeedsFetcher::fetch().
   *
   * @todo: more input validation.
   */
  public function fetch(FeedsSource $source) {
    if (isset($_FILES['xml_submission_file']['tmp_name'])) {
      return FeedsODKBatch($_FILES);
    }
    throw new Exception(t('Invalid submission'));
  }
}